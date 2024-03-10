
// stdafx.h : Included files for standard system include files£¬
// or frequently used but seldom changed

// project-specific include files

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely used data from the Windows header
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Some CString constructors will be explicit

// Turns off the hiding of certain common but often reassuring warning messages from MFC
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extension


#include <afxdisp.h>        // MFC Automation class



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 public controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows public controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbon and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include "iCVSC.h"
#include "iCVSCError.h"
#include "VARender.h"
#include "AudioCapEnc.h"
#include "AudioDecPlay.h"
#include "VARecorder.h"

//#pragma comment(lib, "../Lib/VARndr.lib")
//#pragma comment(lib, "../Lib/iCVSC2.lib")
//#pragma comment(lib, "../Lib/VARecorder.lib")
//#pragma comment(lib, "../Lib/AudioCapEnc.lib")
//#pragma comment(lib, "../Lib/AudioDecPlay.lib")

#pragma comment(lib, "iCVSC2.lib")
#pragma comment(lib, "VARndr.lib")
#pragma comment(lib, "AudioCapEnc.lib")
#pragma comment(lib, "AudioDecPlay.lib")
