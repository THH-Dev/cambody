
// iCVSServerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iCVSServerDemo.h"
#include "iCVSServerDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int WINAPI GetPswByPUIDCallback(const char *pszPUID, unsigned char szPasswordHash[16])
{
	return 0;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CiCVSServerDemoDlg dialog

#define  TIMER_ID_KEEPALIVE					0		// Keep alive timer 
#define  TIMER_ID_PLAY_VIDEO				1		// Play video

CiCVSServerDemoDlg::CiCVSServerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiCVSServerDemoDlg::IDD, pParent)
	, m_szServiceIP(_T("192.168.1.8"))
	, m_szServicePort(_T("49988"))
	, m_szStreamPort(_T("49990"))
	, m_szBindIP(_T("192.168.1.8"))
	, m_pPlayer(NULL)
	, m_pTalkPlayer(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_THH);

	memset(&m_TalkObjInfo, 0, sizeof(m_TalkObjInfo));
}

void CiCVSServerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_szServiceIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_szServicePort);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_szStreamPort);
	DDX_Text(pDX, IDC_EDIT_BIND_IP, m_szBindIP);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStartService);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStopService);
	DDX_Control(pDX, IDC_TREE_RESOURCE, m_treeResource);
	DDX_Control(pDX, IDC_STATIC_PLAYWND, m_stcPlayWnd);
}

BEGIN_MESSAGE_MAP(CiCVSServerDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CiCVSServerDemoDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CiCVSServerDemoDlg::OnBnClickedButtonStop)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_RESOURCE, &CiCVSServerDemoDlg::OnNMDblclkTreeResource)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CiCVSServerDemoDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOPPLAY, &CiCVSServerDemoDlg::OnBnClickedButtonStopplay)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STARTCALL, &CiCVSServerDemoDlg::OnBnClickedButtonStartTalk)
	ON_BN_CLICKED(IDC_BUTTON_STOPCALL, &CiCVSServerDemoDlg::OnBnClickedButtonStopTalk)
	ON_BN_CLICKED(IDC_BUTTON_STARTGPS, &CiCVSServerDemoDlg::OnBnClickedButtonStartgps)
	ON_BN_CLICKED(IDC_BUTTON_STOPGPS, &CiCVSServerDemoDlg::OnBnClickedButtonStopgps)
END_MESSAGE_MAP()


// CiCVSServerDemoDlg message handlers

BOOL CiCVSServerDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CiCVSServerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CiCVSServerDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CiCVSServerDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CiCVSServerDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int rv = 0;
	if (nIDEvent == TIMER_ID_KEEPALIVE)
	{
		IC_HANDLE hSession = NULL;
		// Judge if there is new equipment come to connect
		rv = IC_AcceptSession(&hSession);
		if (rv == 0)
		{
			// It says there's new equipment coming in

			m_saSessions.push_back(hSession);  // Save dialog to a queue of connected devices
			// Get details of the device and displays them in the tree control
			IC_HANDLE hPU = NULL;
			rv = IC_ForkOnePU(hSession, "", &hPU);
			if (rv == 0)
			{
				IC_STR szPUID;
				rv = IC_GetResourcePUID(hPU, szPUID);

				TRACE("PU online!  PUID=%s\r\n", szPUID);


				IC_HANDLE haResArray[100] = { 0 };
				int nArrayCnt = sizeof(haResArray) / sizeof(IC_HANDLE);
				rv = IC_ForkPUResource(hPU, haResArray, &nArrayCnt);
				if (rv == 0)
				{
					IC_STR szName;
					IC_GetResourceName(hPU, szName);
					HTREEITEM hItem = m_treeResource.InsertItem(szName);
					m_treeResource.SetItemData(hItem, (DWORD)hPU);

					for (int i = 0; i < nArrayCnt; i++)
					{
						IC_GetResourceName(haResArray[i], szName);
						HTREEITEM hChildItem = m_treeResource.InsertItem(szName, hItem);
						m_treeResource.SetItemData(hChildItem, (DWORD)haResArray[i]);
					}
				}
			}
		}

		//  Walk through the sessions of all online devices to determine if the device is disconnected
		SESSION_ARR::iterator it = m_saSessions.begin();
		while (it != m_saSessions.end())
		{
			hSession = *it;


			int nType = NOTIFY_TYPE_NORMAL;
			char *szEvent = NULL;
			rv = IC_RecvEventMessageEx(hSession, &nType, &szEvent);
			if (rv == IC_SUCCESS)
			{
				TRACE("recv notify ok, nType = %d, szEvent = %s\r\n", 
					nType, szEvent);
				// Received notification
				IC_ReleaseMessage(hSession, szEvent);
				it++;
			}
			else if (rv != IC_ERROR_MC_WOULDBLOCK)
			{
				// This indicates that the connection to the device has been disconnected
				it = m_saSessions.erase(it);  // Removed from online queue


				// Removes the specified device node from the tree
				HTREEITEM hItem = m_treeResource.GetRootItem();
				while (hItem != NULL)
				{
					IC_HANDLE hCurPU = (IC_HANDLE)m_treeResource.GetItemData(hItem);
					IC_HANDLE hPU = NULL;
					rv = IC_ForkOnePU(hSession, "", &hPU);
					if (rv == 0 && hCurPU == hPU)
					{
						IC_STR szPUID;
						rv = IC_GetResourcePUID(hPU, szPUID);

						TRACE("PU offline!  PUID=%s\r\n", szPUID);

						m_treeResource.DeleteItem(hItem);
						break;
					}
					hItem = m_treeResource.GetNextSiblingItem(hItem);
				}

				// Determine if the device is playing, and if it is, turn it off
				// ...


				// Release device session
				IC_DeleteSession(hSession);
			}
			else
			{
				it++;
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CiCVSServerDemoDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	// Start the reverse SDK service
	CString szInfo;
	int rv = IC_StartService(m_szServiceIP, atoi(m_szServicePort), atoi(m_szStreamPort), m_szBindIP, NULL, NULL);
	if (rv != 0)
	{
		szInfo.Format("IC_StartService error, code = %d", rv);
		AfxMessageBox(szInfo);
		return ;
	}
	else
	{
		szInfo.Format("IC_StartService successs ");
		AfxMessageBox(szInfo);
	}
	// Set live interval (default 15 seconds)
	IC_SetKeepAliveInterval(15);

	SetTimer(TIMER_ID_KEEPALIVE, 100, NULL);
}




void CiCVSServerDemoDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonStopplay();

	KillTimer(TIMER_ID_KEEPALIVE);

	m_treeResource.DeleteAllItems();

	SESSION_ARR::iterator it = m_saSessions.begin();
	for ( ; it != m_saSessions.end(); it++)
	{
		IC_HANDLE hSession = *it;
		IC_DeleteSession(hSession);
	}
	m_saSessions.clear();

	// Stop localservice
	IC_StopService();
}


void CiCVSServerDemoDlg::OnNMDblclkTreeResource(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int rv = 0;
	CString szInfo;
	HTREEITEM hItem = m_treeResource.GetSelectedItem();
	if (hItem == NULL)
	{
		return ;
	}
	DWORD dwData = m_treeResource.GetItemData(hItem);
	if (dwData == NULL)
	{
		return ;
	}
	IC_HANDLE hRsc = (IC_HANDLE)dwData;
	IC_STR szType;
	rv = IC_GetResourceType(hRsc, szType);
	if (strcmp(szType, RESOURCE_TYPE_ST) == 0)
	{
		IC_HANDLE haRes[500];
		int nCount = 500;
		rv = IC_ForkPUResource(hRsc, haRes, &nCount);
		if (rv == 0)
		{
			while(m_treeResource.GetChildItem(hItem) != NULL)
			{
				m_treeResource.DeleteItem(m_treeResource.GetChildItem(hItem));
			}

			for (int i = 0; i < nCount; i++)
			{
				{
					IC_STR szName;
					rv = IC_GetResourceName(haRes[i], szName);
					HTREEITEM hCurItem = m_treeResource.InsertItem(szName, hItem);
					m_treeResource.SetItemData(hCurItem, (DWORD)haRes[i]);
				}	
			}
		}
		else
		{
			szInfo.Format("IC_ForkPUResource error, rv = %d", rv);
			AfxMessageBox(szInfo);
		}
	}
	else if (strcmp(szType, RESOURCE_TYPE_IV) == 0)
	{
		OnBnClickedButtonPlay();
	}
}




void CiCVSServerDemoDlg::OnBnClickedButtonPlay()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButtonStopplay();

	int rv = 0;
	CString szInfo;
	HTREEITEM hItem = m_treeResource.GetSelectedItem();
	if (hItem == NULL)
	{
		return ;
	}
	DWORD dwData = m_treeResource.GetItemData(hItem);
	if (dwData == NULL)
	{
		return ;
	}
	IC_HANDLE hRsc = (IC_HANDLE)dwData;
	IC_STR szType;
	rv = IC_GetResourceType(hRsc, szType);
	if (strcmp(szType, RESOURCE_TYPE_IV) == 0)
	{
		m_pPlayer = new CiCVSPlayer();
		int streamID = 0;  // Plays the main stream
		rv = m_pPlayer->start(hRsc, streamID, m_stcPlayWnd.GetSafeHwnd());
		if (rv != 0)
		{
			delete m_pPlayer;
			m_pPlayer = NULL;
		}
	}
}


void CiCVSServerDemoDlg::OnBnClickedButtonStopplay()
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->stop();
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
}


void CiCVSServerDemoDlg::OnBnClickedButtonStartTalk()
{
	OnBnClickedButtonStopTalk();

	int rv = 0;
	CString szInfo;
	HTREEITEM hItem = m_treeResource.GetSelectedItem();
	if (hItem == NULL)
	{
		return ;
	}
	DWORD dwData = m_treeResource.GetItemData(hItem);
	if (dwData == NULL)
	{
		return ;
	}
	IC_HANDLE hRsc = (IC_HANDLE)dwData;
	IC_STR szType;
	rv = IC_GetResourceType(hRsc, szType);

	if (strcmp(szType, RESOURCE_TYPE_ST) == 0)
	{
		// Select the device node to find the intercom resource of the device
		IC_HANDLE hpu = NULL;
		rv = IC_GetPUHandle(hRsc, &hpu);
		if(rv != 0)
		{
			szInfo.Format("IC_GetPUHandle error, error is %d", rv);
			AfxMessageBox(szInfo);
			return;
		}
		IC_HANDLE hRes = NULL;
		rv = IC_GetResourceHandle(hpu, RESOURCE_TYPE_OA, 0, &hRes);
		if(rv != 0)
		{
			szInfo.Format("IC_GetResourceHandle error, error is %d", rv);
			AfxMessageBox(szInfo);
			return;
		}
		hRsc = hRes;
	}
	else if (strcmp(szType, RESOURCE_TYPE_OA) == 0)
	{
		// Intercom resources, support intercom
		TRACE("Intercom resources, support intercom");
	}
	else
	{
		// Other types do not support intercom
		TRACE("Other types do not support intercom");
		return;
	}

	if ( m_pTalkPlayer == NULL)
	{
		m_pTalkPlayer = new CiCVSTalkPlayer();
		rv = m_pTalkPlayer->start(hRsc);
		if (rv != 0)
		{
			szInfo.Format("m_pTalkPlayer start, error is %d", rv);
			AfxMessageBox(szInfo);
			delete m_pTalkPlayer;
			m_pTalkPlayer = NULL;
		}
	}
}


void CiCVSServerDemoDlg::OnBnClickedButtonStopTalk()
{
	if (m_pTalkPlayer != NULL)
	{
		m_pTalkPlayer->stop();
		delete m_pTalkPlayer;
		m_pTalkPlayer = NULL;
	}
}



void CiCVSServerDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	OnBnClickedButtonStop();
}

IC_HANDLE CiCVSServerDemoDlg::getSlelectedPTZHandle()
{
	int rv = 0;
	CString szInfo;
	HTREEITEM hItem = m_treeResource.GetSelectedItem();
	if (hItem == NULL)
	{
		return NULL;
	}
	DWORD dwData = m_treeResource.GetItemData(hItem);
	if (dwData == NULL)
	{
		return NULL;
	}
	IC_HANDLE hRsc = (IC_HANDLE)dwData;
	IC_STR szType;
	rv = IC_GetResourceType(hRsc, szType);
	IC_HANDLE hPU = NULL;
	if (strcmp(szType, RESOURCE_TYPE_ST) == 0)
	{
		hPU = hRsc;
	}
	else
	{
		rv = IC_GetPUHandle(hRsc, &hPU);
		if (rv != 0)
		{
			return NULL;
		}
	}
	IC_HANDLE hPTZ = NULL;
	rv = IC_GetResourceHandle(hPU, RESOURCE_TYPE_PTZ, 0, &hPTZ);
	if (rv != 0)
	{
		return NULL;
	}
	return hPTZ;
}
BOOL CiCVSServerDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	// Gets PTZ resource for the currently selected resource
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_TURN_UP)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_StartTurnUp(hPTZ, 0);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopTurn(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_TURN_DOWN)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_StartTurnDown(hPTZ, 0);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopTurn(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_TURN_LEFT)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_StartTurnLeft(hPTZ, 0);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopTurn(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_TURN_RIGHT)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_StartTurnRight(hPTZ, 0);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopTurn(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_FOCUS_FAR)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_MakeFocusFar(hPTZ);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopFocusMove(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_FOCUS_NEAR)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_MakeFocusNear(hPTZ);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopFocusMove(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_IN)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_ZoomInPicture(hPTZ);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopPictureZoom(hPTZ);
		}
	}
	if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZOOM_OUT)->m_hWnd)
	{
		IC_HANDLE hPTZ = getSlelectedPTZHandle();
		if (hPTZ == NULL)
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			IC_ZoomOutPicture(hPTZ);
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			IC_StopPictureZoom(hPTZ);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}






void CiCVSServerDemoDlg::OnBnClickedButtonStartgps()
{
	// TODO: Add your control notification handler code here
	int rv = 0;
	CString szInfo;
	HTREEITEM hItem = m_treeResource.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}
	DWORD dwData = m_treeResource.GetItemData(hItem);
	if (dwData == NULL)
	{
		return;
	}
	IC_HANDLE hRsc = (IC_HANDLE)dwData;
	IC_STR szType;
	rv = IC_GetResourceType(hRsc, szType);
	if (strcmp(szType, RESOURCE_TYPE_GPS) == 0)
	{
		//m_pPlayer = new CiCVSPlayer();
		//int streamID = 0;  // Plays the main stream
		//rv = m_pPlayer->start(hRsc, streamID, m_stcPlayWnd.GetSafeHwnd());
		//if (rv != 0)
		//{
		//	delete m_pPlayer;
		//	m_pPlayer = NULL;
		//}

		IC_GNSS_DATA data_gps;
		data_gps.init();
		rv = IC_ReceiveGPSFrame(hRsc, &data_gps);

		if (rv == 0)
		{
			data_gps.print();
		}
		else
		{
			TRACE("TACH\n");
			data_gps.print();
		}
	}
}


void CiCVSServerDemoDlg::OnBnClickedButtonStopgps()
{
	// TODO: Add your control notification handler code here
	std::cout << "uiUTC = " << 123 << std::endl;
}
