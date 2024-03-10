#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// VodOnTimeDialog dialog

class VodOnTimeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(VodOnTimeDialog)

public:
	VodOnTimeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~VodOnTimeDialog();

// Dialog Data
	enum { IDD = IDD_VODTIMEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	char *m_pFrameData;
	int m_nBufLen;

public:
	afx_msg void OnBnClickedButtonVodtime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStopvod(); 
	int m_nBeginTime;
	int m_nEndTime;
	CDateTimeCtrl m_datetimeControlBegin;
	CDateTimeCtrl m_datetimeControEnd;
	CButton m_vodTimeButton;
	CButton m_cancelVodTimeButton;
	CStatic m_playVodWnd;


	CString m_szVodID;
	IC_HANDLE m_hVADR;
	IC_HANDLE m_hStream;
	bool m_bIsVodPaused;

	IC_HANDLE m_hSession;
	IC_HANDLE m_hRes;
};
