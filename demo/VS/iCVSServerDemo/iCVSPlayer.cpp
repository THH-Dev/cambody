#include "stdafx.h"
#include "iCVSPlayer.h"


DWORD WINAPI _ThreadPorc( LPVOID lpParam ) 
{ 
	CiCVSPlayer *player = (CiCVSPlayer *)lpParam;
	player->threadRun();
	return 0; 
} 


CiCVSPlayer::CiCVSPlayer(void)
	:m_hIV(NULL)
	,m_hStream(NULL)
	,m_bThreadStopFlag(true)
	,m_hVARender(NULL)
{
	m_nBufLen = 1024*1024*4;
	m_pFrameBuf = new char[m_nBufLen];
}

CiCVSPlayer::~CiCVSPlayer(void)
{
	
}

int CiCVSPlayer::start(HANDLE hIV, int nStreamID, HWND hWnd)
{
	int rv = 0;
	rv = VARender_Open(&m_hVARender);
	if (rv != VARENDER_E_OK)
	{
		return rv;
	}
	VARender_SetWindow(m_hVARender, hWnd);
	VARender_SetDDraw(m_hVARender, 1);  // Set ddraw mode to play

	VARender_StartVideo(m_hVARender);

	VARender_StartAudio(m_hVARender);

	// Start playback stream
	rv = IC_StartStream(hIV, nStreamID, &m_hStream);
	if (rv != 0)
	{
		
		return rv;
	}
	m_bThreadStopFlag = false;
	m_hThread = CreateThread(NULL, 0,   _ThreadPorc,  this,  0, NULL);  
	return 0;
}

int CiCVSPlayer::stop()
{
	if (!m_bThreadStopFlag)
	{
		// Close fetch and decode thread
		m_bThreadStopFlag = true;
		WaitForSingleObject(m_hThread, INFINITE);

		// Stop play stream
		IC_StopStream(m_hStream);
		m_hStream = NULL;

		VARender_Close(m_hVARender);
		m_hVARender = NULL;

	}
	return 0;
}

int CiCVSPlayer::threadRun()
{
	int rv = 0;
	while (!m_bThreadStopFlag)
	{
		// 
		int nFrmType = 0;
		int nKeyFrmFlag = 0;
		bool bContinueReceiveFrame = true;
		while (bContinueReceiveFrame)
		{
			/*
			// test begin
			{
				// Test to obtain PS stream
				int nLen = m_nBufLen;
				rv = IC_ReceivePSFrame(m_hStream, m_pFrameBuf, &nLen);
				if (rv != 0)
				{
					switch (rv)
					{
					case IC_ERROR_DC_WOULDBLOCK:
					case IC_ERROR_DCS_WOULDBLOCK:
						bContinueReceiveFrame = false;  // Stop receiving flow
						break;
					default:
						// It indicates the stream is broken, need                                                 IC_StopStream,and then IC_StartStream again break;
					}
				}
				else
				{
					// Save PS stream
					FILE *fp = fopen("C:/PSFrame.data", "a+b");
					if (fp != NULL)
					{
						fwrite(m_pFrameBuf, 1, nLen, fp);
						fclose(fp);
					}
				}
				break;
			}
			// test end
			*/

			// Take the stream from the platform
			int nLen = m_nBufLen;
			rv = IC_ReceiveFrame(m_hStream, m_pFrameBuf, &nLen, &nFrmType, &nKeyFrmFlag);
			if (rv != 0)
			{
				switch (rv)
				{
				case IC_ERROR_DC_WOULDBLOCK:
				case IC_ERROR_DCS_WOULDBLOCK:
					bContinueReceiveFrame = false;  // Stop receiving flow
					break;
				default:
					break;
					// It indicates the stream is broken, need IC_StopStream,                                            and then IC_StartStream again break;
				}
			}
			else
			{

				//TRACE("nFrmType = %d\n", nFrmType);
				if (nFrmType == FRAME_TYPE_VIDEO)  // Video data frame
				{
					VARender_PumpVideoFrame(m_hVARender, m_pFrameBuf, nLen);
				}
				else if (nFrmType == FRAME_TYPE_AUDIO) // Audio data frames (this is the audio accompanying the video)
				{
					
					VARender_PumpAudioFrame(m_hVARender, m_pFrameBuf, nLen);	
				}else if (nFrmType == FRAME_TYPE_GPS) // gps
				{
					
					TRACE("nFrmType = %d\n GPS", nFrmType);
				}
				else
				{
					TRACE("nFrmType = %d\n", nFrmType);
				}
			}
		}
		Sleep(33);
	}
	return 0;
}