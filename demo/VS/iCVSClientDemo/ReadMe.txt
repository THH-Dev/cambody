==============================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : iCVSClientDemo Project Overview
==============================================================================

The application wizard has created this iCVSClientDemo application for
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.


This file Outlines the contents of each of the files that make up the iCVSClientDemo application.
iCVSClientDemo.vcxproj
    This is the main project file for the VC++ project generated using the application wizard. It contains the version of the Visual C++ that generated the file, as well as information about the platform, configuration, and project functionality selected using the application wizard

iCVSClientDemo.vcxproj.filters
    This is the VC++ project filter file generated using the application wizard. It contains information about the association between the project file and the filter. In an IDE, through this association, files with similar extensions are grouped under a particular node. For example, the.cpp file is associated with the source file filter.

iCVSClientDemo.h
   This is the main header file for the application.
This includes other project-specific headers (including resource-h) and declares the CiCVSClientDemoApp application class.

iCVSClientDemo.cpp
   This is the main application source file that contains the application class CiCVSClientDemoApp.

iCVSClientDemo.rc
    This is a list of all Microsoft Windows resources used by the program. It includes ICONS, bitmaps, and cursors stored in the RES subdirectory. This file can be edited directly from Microsoft Visual C++. Project resources are included in 2052.  

res\iCVSClientDemo.ico
    This is the icon file used as the application icon. This icon is included in the main resource file icvsclientdemo.rc.

res\iCVSClientDemo.rc2
   This file contains resources that are not edited in Microsoft Visual C++. You should put all resources in this file that are not editable by the resource editor.


/////////////////////////////////////////////////////////////////////////////

Application wizard creates a dialog class:

Icvsclientdemodlg.h, icvsclientdemodlg.cpp - dialog box
These files contain the CiCVSClientDemoDlg class. This class defines the behavior of the application's main dialog box. The dialog template is included in icvsclientdemo.rc, which can be edited in Microsoft Visual C++.
/////////////////////////////////////////////////////////////////////////////

Other functions:

ActiveX control
The application includes support for using ActiveX controls.

/////////////////////////////////////////////////////////////////////////////

Other standard documents:

StdAfx. J h, StdAfx. CPP
    These files are used to generate a precompiled header (PCH) file named icvsclientdemo.pch and a precompiled type file named stdafx.obj.

The Resource. H
    This is the standard header file that you can use to define the new resource ID. Microsoft Visual C++ will read and update this file.

ICVSClientDemo. The manifest
    Windows XP USES the application manifest file to describe the application dependencies of a particular version of a parallel assembly. The loader USES this information to load the appropriate assembly from the assembly cache and protect it from access by the application. The application manifest may be included to be redistributed as an external.manifest file installed in the same folder as the application executable, or it may be included as a resource in the executable. /////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard USES "TODO:" to indicate which parts of the source code should be added or customized.

If your application USES MFC in a Shared DLL, you will need to redistribute the MFC DLL. If the language used by the application is different from the operating system locale, the corresponding localization resource mfc110xxx. DLL also needs to be redistributed.
For more information on the above topic, see the section on redistributing Visual C++ applications in the MSDN documentation.
/////////////////////////////////////////////////////////////////////////////
