// VodOnTimeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "iCVSClientDemo.h"
#include "iCVSClientDemoDlg.h"
#include "VodOnTimeDialog.h"
#include "afxdialogex.h"

#define  TIMER_ID_VODTIME						0		//Timedemand

// VodOnTimeDialog dialog

IMPLEMENT_DYNAMIC(VodOnTimeDialog, CDialogEx)

VodOnTimeDialog::VodOnTimeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(VodOnTimeDialog::IDD, pParent)
	,m_bIsVodPaused(FALSE)
	,m_hVADR(NULL)
	,m_hStream(NULL)
{
	m_nBufLen = 1024 * 1024;
	m_pFrameData = new char[m_nBufLen];
	memset(m_pFrameData,'\0', sizeof(m_pFrameData));
}

VodOnTimeDialog::~VodOnTimeDialog()
{
	if(m_hStream != NULL )
	{
		IC_StopStream(m_hStream);
	}
	if (m_hVADR != NULL)
	{
		VARender_Close(m_hVADR);
		m_hVADR = NULL;
	}
	m_hSession = NULL;
	m_hRes = NULL;;
}

void VodOnTimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKERBEGIN, m_datetimeControlBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKEREND, m_datetimeControEnd);
	DDX_Control(pDX, IDC_BUTTON_VODTIME, m_vodTimeButton);
	DDX_Control(pDX, IDSTOPVOD, m_cancelVodTimeButton);
	DDX_Control(pDX, IDC_STATIC_WND1, m_playVodWnd);
}


BEGIN_MESSAGE_MAP(VodOnTimeDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VODTIME, &VodOnTimeDialog::OnBnClickedButtonVodtime)
	ON_BN_CLICKED(IDSTOPVOD, &VodOnTimeDialog::OnBnClickedStopvod)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void VodOnTimeDialog::OnBnClickedButtonVodtime()
{
	// TODO: Add your control notification handler code here
	CTime tBeginTime;
	CTime tEndTime;
	m_datetimeControlBegin.GetTime(tBeginTime);
	m_datetimeControEnd.GetTime(tEndTime);

	m_nBeginTime = tBeginTime.GetTime();
	m_nEndTime = tEndTime.GetTime();

	IC_STR szVodID;	
	IC_HANDLE hStream = NULL;
	int nRate = 1;

	int rv = IC_CSSVODTime(m_hSession, m_hRes, m_nBeginTime, m_nEndTime, nRate, szVodID, &hStream);
	if(rv != 0)
	{
		CString strInfo;
		strInfo.Format("IC_CSSVODTime error, error is %d", rv);
		MessageBox(strInfo);
		return;
	}

	m_szVodID = szVodID;
	if (m_hVADR != NULL)
	{
		VARender_Close(m_hVADR);
		m_hVADR = NULL;
	}
	m_hStream = hStream;
	rv = VARender_Open(&m_hVADR);
	if(rv != 0)
	{
		CString szInfo;
		szInfo.Format("VARender_Open error, rv = %d", rv);
		AfxMessageBox(szInfo);
		return;
	}
	VARENDER_HWND hWnd = (VARENDER_HWND)m_playVodWnd.m_hWnd;
	rv = VARender_SetWindow(m_hVADR, hWnd);
	if(rv != 0 && rv != -1)
	{
		CString szInfo;
		szInfo.Format("VARender_SetWindow error, rv = %d", rv);
		AfxMessageBox(szInfo);
		return;
	}
	VARender_StartVideo(m_hVADR);
	VARender_StartAudio(m_hVADR);
	SetTimer(TIMER_ID_VODTIME, 50, NULL);
}


void VodOnTimeDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int rv = 0;
	if (nIDEvent == TIMER_ID_VODTIME)
	{
		bool bIsCloseStream = FALSE;
		for(int i = 0; i < 1; i++)
		{
			if (m_hVADR == NULL || m_hStream == NULL)
			{
				bIsCloseStream = TRUE;
				break;
			}
			int nLen = m_nBufLen;
			int nFrmType = 0;
			int nKeyFrmFlag = 0;
			rv = IC_ReceiveFrame(m_hStream, m_pFrameData, &nLen, &nFrmType, &nKeyFrmFlag);
			if (rv == 0)
			{
				if (nFrmType == FRAME_TYPE_VIDEO)
				{
					VARender_PumpVideoFrame(m_hVADR, m_pFrameData, nLen);
				}
				else if (nFrmType == FRAME_TYPE_AUDIO)
				{
					VARender_PumpAudioFrame(m_hVADR, m_pFrameData, nLen);
				}

			}
			else if (rv != IC_ERROR_DC_WOULDBLOCK)
			{
				//bIsCloseStream = TRUE;
				break;
			}
		}

		if (bIsCloseStream)
		{
			KillTimer(TIMER_ID_VODTIME);
			if(m_hStream != NULL)
			{
				IC_StopStream(m_hStream);
				m_hStream = NULL;
			}
			if(m_hVADR != NULL)
			{
				VARender_Close(m_hVADR);
				m_hVADR = NULL;
			}

			if(rv == IC_ERROR_END)
			{				
				AfxMessageBox("Play finished!");		
			}
			else if (rv != IC_ERROR_DC_WOULDBLOCK)
			{
				CString szInfo;
				szInfo.Format("[%d][%d] IC_ReceiveFrame error, rv = %d\r\n",0, 0, rv);
				AfxMessageBox(szInfo);
			}
		}
	}
		
	CDialogEx::OnTimer(nIDEvent);
}


void VodOnTimeDialog::OnBnClickedStopvod()
{
	// TODO: Add your control notification handler code here
	int rv = 0;
	if(m_szVodID.IsEmpty())
		return;

	if(!m_bIsVodPaused)
	{
		rv = IC_CSSVODPause(m_hSession, m_szVodID);
		if(rv != 0)
		{
			CString szInfo;
			szInfo.Format("IC_CSSVODPause error, rv = %d", rv);
			AfxMessageBox(szInfo);
			return;
		}
		SetDlgItemText(IDSTOPVOD, "Pause");
		m_bIsVodPaused = TRUE;
	}
	else
	{
		rv = IC_CSSVODResume(m_hSession, m_szVodID);
		if(rv != 0)
		{
			CString szInfo;
			szInfo.Format("IC_CSSVODResume error, rv = %d", rv);
			AfxMessageBox(szInfo);
			return;
		}
		SetDlgItemText(IDSTOPVOD, "Recover");
		m_bIsVodPaused = FALSE;
	}
}
