// DlgTimeSlice.cpp : implementation file
//

#include "stdafx.h"
#include "iCVSClientDemo.h"
#include "DlgTimeSlice.h"
#include "afxdialogex.h"


// CDlgTimeSlice dialog

IMPLEMENT_DYNAMIC(CDlgTimeSlice, CDialogEx)

CDlgTimeSlice::CDlgTimeSlice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTimeSlice::IDD, pParent)
	, m_tBegin(0)
	, m_tEnd(0)
{

}

CDlgTimeSlice::~CDlgTimeSlice()
{
}

void CDlgTimeSlice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN_DATE, m_dtcBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_dtcEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN_DATE, m_tBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_tEnd);
	DDX_Control(pDX, IDC_EDITSAVEFILEPATH, m_downloadSliceFilePath);
}


BEGIN_MESSAGE_MAP(CDlgTimeSlice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONOPENFILEROUTE, &CDlgTimeSlice::OnBnClickedButtonopenfileroute)
	ON_BN_CLICKED(IDOK, &CDlgTimeSlice::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTimeSlice message handlers

void CDlgTimeSlice::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

BOOL CDlgTimeSlice::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_dtcBegin.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_dtcBegin.SetTime(&CTime::GetCurrentTime());

	m_dtcEnd.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_dtcEnd.SetTime(&CTime::GetCurrentTime());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTimeSlice::OnBnClickedButtonopenfileroute()
{
	// TODO: Add your control notification handler code here
	CString strDefaultPath;
	char chPath[512];
	GetModuleFileName(NULL,chPath,512);		//Get the file name of the executing program (including the path);
	strDefaultPath.Format("%s",chPath);			//Convert to string£»
	int nPos = strDefaultPath.ReverseFind('\\');	//Find the first "\\" character from the right and return the position of its array index
	strDefaultPath = strDefaultPath.Left(nPos+1);			//Preserve the first nPos+1 character of the string (including "\\");
	
	CString fileName = _T("test.avi");			//The file name that is opened by default
	CString filter = _T(" file (*.avi");	//The type of file filter
	CFileDialog openFileDlg(FALSE, strDefaultPath, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = _T("E:\\FileTest\\test.avi");
	INT_PTR result = openFileDlg.DoModal();
	m_strFilePath = strDefaultPath + "\\" + fileName;
	if(result == IDOK) {
		m_strFilePath = openFileDlg.GetPathName();
	}
	m_downloadSliceFilePath.SetWindowTextA(m_strFilePath);
}
