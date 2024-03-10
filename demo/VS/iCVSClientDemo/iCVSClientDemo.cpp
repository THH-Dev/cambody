
// iCVSClientDemo.cpp : Defines the class behavior of the application.
//

#include "stdafx.h"
#include "iCVSClientDemo.h"
#include "iCVSClientDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiCVSClientDemoApp

BEGIN_MESSAGE_MAP(CiCVSClientDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CiCVSClientDemoApp structure

CiCVSClientDemoApp::CiCVSClientDemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CiCVSClientDemoApp object

CiCVSClientDemoApp theApp;


// CiCVSClientDemoApp initialization

BOOL CiCVSClientDemoApp::InitInstance()
{
	// if an application listing running on Windows XP specifies to
        
// use comctl32.dll version 6 or later to enable visualization,

        // InitCommonControlsEx() is required. Otherwise, the window cannot be created.
        INITCOMMONCONTROLSEX InitCtrls;

        InitCtrls.dwSize = sizeof (InitCtrls);
        
// set it to include everything to be used in the application
// public control class.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CString szDllPath("C:\\ProgramData\\iCVS2\\OEMCodec\\");
	int rv = IC_Initialize();
	ASSERT(rv == 0);
	rv = VARender_Startup(szDllPath);
	//rv = VARender_Startup(NULL);
	ASSERT(rv == 0);

	rv = AudioCapEnc_Startup(szDllPath);
	ASSERT(rv == 0);

	rv = AudioDecPlay_Startup(szDllPath);
	ASSERT(rv == 0);

	rv = VARecorder_Startup(szDllPath);
	ASSERT(rv == 0);

	CiCVSClientDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: when to place processing here

                // "ok" to close the dialog box code
}
else if (nResponse == IDCANCEL)
{
                
// TODO: when to place processing here

                // "cancel" to close the dialog box code
}
else if (nResponse == -1)
{
TRACE(traceAppMsg, 0, "warning: dialog creation failed, application will terminate unexpectedly. \ n ");
TRACE(traceAppMsg, 0, "warning: if you use the MFC control on the dialog box, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS. \ n ");
	}

	VARecorder_Cleanup();
	AudioDecPlay_Cleanup();
	AudioCapEnc_Cleanup();
	VARender_Cleanup();
	IC_Terminate();

	// // Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

