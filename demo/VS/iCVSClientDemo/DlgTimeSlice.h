#pragma once
#include "atltime.h"
#include "afxdtctl.h"
#include "afxwin.h"


// CDlgTimeSlice dialog

class CDlgTimeSlice : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTimeSlice)

public:
	CDlgTimeSlice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTimeSlice();

// Dialog Data
	enum { IDD = IDD_DIALOG_TIMESLICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CDateTimeCtrl m_dtcBegin;
	CDateTimeCtrl m_dtcEnd;
	CTime m_tBegin;
	CTime m_tEnd;
	CString m_strFilePath;
	afx_msg void OnBnClickedButtonopenfileroute();
	CEdit m_downloadSliceFilePath;
	afx_msg void OnBnClickedOk();
	void sethSession(IC_HANDLE hsession);
	void setCameraRes(IC_HANDLE hRes);
	IC_HANDLE m_hSession;
	IC_HANDLE m_hRes;
};
