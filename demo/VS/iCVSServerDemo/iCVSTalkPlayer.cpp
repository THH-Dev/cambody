#include "stdafx.h"
#include "iCVSTalkPlayer.h"


DWORD WINAPI _ThreadTalkPorc( LPVOID lpParam ) 
{ 
	CiCVSTalkPlayer *player = (CiCVSTalkPlayer *)lpParam;
	player->threadRun();
	return 0; 
} 


CiCVSTalkPlayer::CiCVSTalkPlayer(void)
	:m_hST(NULL)
	,hTalkStream(NULL)
	,m_bThreadStopFlag(true)
{
	m_nBufLen = 1024 * 1024;
	m_pFrameData = new char[m_nBufLen];
	memset(m_pFrameData,'\0', sizeof(m_pFrameData));
	ASSERT(m_pFrameData != NULL);
}

CiCVSTalkPlayer::~CiCVSTalkPlayer(void)
{

}

int CiCVSTalkPlayer::start(IC_HANDLE hST)
{
	int rv = 0;
	if(hTalkStream != NULL) 
	{
		IC_StopStream(hTalkStream);
		hTalkStream = NULL;
	}
	rv = AudioCapEnc_Open(1, "G711U", 0, &hAudioCapEnc);
	if(rv != 0)
	{
		return rv;
	}
	rv = AudioDecPlay_Open(&hAudioDecPlay);
	if(rv != 0)
	{
		return rv;
	}

	rv = IC_StartTalk(hST, &hTalkStream);
	if(rv != 0)
	{
		return rv;
	}

	m_bThreadStopFlag = false;
	m_hThread = CreateThread(NULL, 0,   _ThreadTalkPorc,  this,  0, NULL);  
	return 0;
}

int CiCVSTalkPlayer::stop()
{
	if (!m_bThreadStopFlag)
	{
		// Close fetch stream and decode thread
		m_bThreadStopFlag = true;
		WaitForSingleObject(m_hThread, INFINITE);

		// Stop play stream
		if (hAudioCapEnc != NULL)
		{
			AudioCapEnc_Close(hAudioCapEnc);
			hAudioCapEnc = NULL;
		}

		if (hAudioDecPlay != NULL)
		{
			AudioDecPlay_Close(hAudioDecPlay );
			hAudioDecPlay  = NULL;
		}

		if (hTalkStream != NULL)
		{
			int rv = IC_StopStream(hTalkStream);
			if(rv != 0)
			{
				return rv;
			}
			hTalkStream = NULL;
		}

	}
	return 0;
}

int CiCVSTalkPlayer::threadRun()
{
	while (!m_bThreadStopFlag)
	{
		if(hTalkStream != NULL)
		{
			CString strInfo;
			bool bCloseStream = false;
			int nLen = m_nBufLen;
			int nFrmType = 0;
			int nKeyFrmFlag = 0;
			// Receive intercom flow from the device
			int rv = IC_ReceiveFrame(hTalkStream, m_pFrameData, &nLen, &nFrmType, &nKeyFrmFlag);
			if (rv != IC_SUCCESS)
			{
				if (rv == IC_ERROR_DCS_WOULDBLOCK)
				{
					// This means that there is no audio data coming from the device
				}
				else
				{
					strInfo.Format("Talk IC_ReceiveFrame error, rv = %d\r\n", rv);
					TRACE("Talk IC_ReceiveFrame error, rv = %d\r\n", rv);
					bCloseStream = true;
				}
			}
			else
			{
				// Decoding playback audio
				AudioDecPlay_PumpFrame(hAudioDecPlay, m_pFrameData, nLen);
			}
			// The capture and encoding of audio from the local microphone
			nLen = AudioCapEnc_ReadFrame(hAudioCapEnc, m_pFrameData, m_nBufLen);
			if (nLen > 0)
			{
				// Data send to device side
				rv = IC_SendFrame(hTalkStream, m_pFrameData, nLen, FRAME_TYPE_AUDIO);
				if (rv < 0)
				{
					strInfo.Format("Talk IC_SendFrame error, rv = %d\r\n", rv);
					TRACE("Talk IC_SendFrame error, rv = %d\r\n", rv);
					bCloseStream = true;
				}
				else if (rv == 0)
				{
					TRACE("Talk IC_SendFrame ok, len = %d\r\n", nLen);
				}
			}
			else if (nLen < 0)
			{
				strInfo.Format("Talk AudioCapEnc_ReadFrame error, error = %d \r\n", nLen);
				TRACE("Talk AudioCapEnc_ReadFrame error\r\n");
				bCloseStream = true;
			}

			if (bCloseStream)
			{
				this->stop();
				//AfxMessageBox(strInfo);
			}
		}
	}

	return 0;
}