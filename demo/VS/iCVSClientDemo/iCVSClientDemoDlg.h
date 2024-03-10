
// iCVSClientDemoDlg.h : Head file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define MAX_PLAY_NUM	2
#define MAX_STREAM_NUM	3


// CiCVSClientDemoDlg Dialog box
class CiCVSClientDemoDlg : public CDialogEx
{
// Structure
public:
	CiCVSClientDemoDlg(CWnd* pParent = NULL);	// Standard constructor

// Dialog box data
	enum { IDD = IDD_ICVSCLIENTDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// realize
protected:
	HICON m_hIcon;

	IC_HANDLE m_hSession;
	int m_nCurWnd;

	IC_HANDLE m_hTalkStream;
	AUDIOCAPENC_HANDLE m_hAudioCapEnc;
	AUDIODECPLAY_HANDLE m_hAudioDecPlay;

	struct PLAY_OBJ_INFO
	{
		IC_HANDLE hStream[MAX_STREAM_NUM];
		IC_HANDLE hPTZ;
		IC_HANDLE hOA;
		HANDLE hVADR;
	};
	PLAY_OBJ_INFO m_PlayObjInfo[MAX_PLAY_NUM];

	char *m_pFrameData;
	int m_nBufLen;

	IC_HANDLE m_hDownload;
	IC_HANDLE m_hUpload;
	FILE *m_pDownFile;
	FILE *m_pUploadFile;

	IC_HANDLE m_hDownloadSlice;
	VARECORDER_HANDLE m_hRecorder;

	char m_pSendData[150 * 1024];
	int m_nSendLen;
	int m_nSendFrmType;
	BOOL m_bSendEndPacket;

	CString m_szManualStorageID;
	CString m_szVodID;

	// The generated message mapping function
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Whether to choose cloud storage
	BOOL IsCloudStorage(void) const
	{
		return m_comboStorageType.GetCurSel() == 0 ? TRUE : FALSE;
	}

	// Whether to choose video recording
	BOOL IsRecordType(void) const
	{
		return m_comboFileType.GetCurSel() == 0 ? TRUE : FALSE;
	}

public:
	CString m_szAddr;
	CString m_szUser;
	CString m_szEPID;
	CString m_szPassword;
	CTreeCtrl m_treeResource;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkTreeResource(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_stcWnd1;
	CStatic m_stcWnd2;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonQuery();
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonVod();
	afx_msg void OnBnClickedButtonUpload();
	CListCtrl m_listFileInfo;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	UINT m_uiPresetPositionNo;
	afx_msg void OnBnClickedButtonTest1();
	CString m_szStreamID;
	CString m_szAlg;
	CString m_szResolution;
	CString m_szFrameRate;
	CString m_szBitRate;
	afx_msg void OnBnClickedButtonStarttalk();
	afx_msg void OnBnClickedButtonStoptalk();
	CComboBox m_comboFileType;
	CComboBox m_comboStorageType;
	afx_msg void OnBnClickedButtonDownloadSlice();
	BOOL m_bFixAddr;
};
