#pragma once
class CiCVSPlayer
{
public:
	CiCVSPlayer(void);
	~CiCVSPlayer(void);

	int start(IC_HANDLE hIV, int nStreamID, HWND hWnd);
	int stop();
public:
	int threadRun();


private:
	VARENDER_HANDLE m_hVARender;
	IC_HANDLE m_hIV;
	IC_HANDLE m_hStream;
	HANDLE m_hThread;
	BOOL m_bThreadStopFlag;

	char *m_pFrameBuf;
	int m_nBufLen;
};

