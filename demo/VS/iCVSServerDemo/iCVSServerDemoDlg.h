
// iCVSServerDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "iCVSPlayer.h"
#include "iCVSTalkPlayer.h"

typedef std::vector<IC_HANDLE> SESSION_ARR;

// CiCVSServerDemoDlg dialog
class CiCVSServerDemoDlg : public CDialogEx
{
// Construction
public:
	CiCVSServerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ICVSSERVERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
	SESSION_ARR m_saSessions;		//Connected device session queue
	CiCVSPlayer *m_pPlayer;			// Player
	CiCVSTalkPlayer *m_pTalkPlayer;	// Intercom player


	IC_HANDLE getSlelectedPTZHandle();



	//¶Ô½²
	struct TALK_OBJ_INFO
	{
		IC_HANDLE hTalkStream;
		AUDIOCAPENC_HANDLE hAudioCapEnc;
		AUDIODECPLAY_HANDLE hAudioDecPlay;
	} m_TalkObjInfo;


public:
	CString m_szServiceIP;
	CString m_szServicePort;
	CString m_szStreamPort;
	CString m_szBindIP;
	CButton m_btnStartService;
	CButton m_btnStopService;
	CTreeCtrl m_treeResource;
	CStatic m_stcPlayWnd;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnNMDblclkTreeResource(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStopplay();
	afx_msg void OnBnClickedButtonStartTalk();
	afx_msg void OnBnClickedButtonStopTalk();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedButtonStartgps();
	afx_msg void OnBnClickedButtonStopgps();
};
