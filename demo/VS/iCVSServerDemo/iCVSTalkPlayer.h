#pragma once
class CiCVSTalkPlayer
{
public:
	CiCVSTalkPlayer(void);
	~CiCVSTalkPlayer(void);

	int start(IC_HANDLE hST);
	int stop();
public:
	int threadRun();


private:
	IC_HANDLE m_hST;
	IC_HANDLE hTalkStream;
	AUDIOCAPENC_HANDLE hAudioCapEnc;
	AUDIODECPLAY_HANDLE hAudioDecPlay;

	char *m_pFrameData;

	HANDLE m_hThread;
	BOOL m_bThreadStopFlag;

	char *m_pFrameBuf;
	int m_nBufLen;
};

