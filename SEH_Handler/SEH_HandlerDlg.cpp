// SEH_HandlerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SEH_Handler.h"
#include "SEH_HandlerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_Output;


// CSEHHandlerDlg dialog

CSEHHandlerDlg::CSEHHandlerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEH_HANDLER_DIALOG, pParent)
	, m_CreateMiniDump(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSEHHandlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EXCEPTIONS_LIST, m_List);
	DDX_Control(pDX, ID_MINIDUMP_BOX, m_MiniDumpButton);
	DDX_Text(pDX, ID_EXCEPTION_RES, g_Output);
	DDX_Control(pDX, ID_EXCEPTION_RES, m_ControlOutput);
}

BEGIN_MESSAGE_MAP(CSEHHandlerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_MINIDUMP_BOX, &CSEHHandlerDlg::OnMiniDumpBtnClicked)
	ON_BN_CLICKED(ID_RAISE_EXCEPTION, &CSEHHandlerDlg::OnRaiseExceptionBtnClicked)
	ON_BN_CLICKED(ID_CLEAN_OUTPUT, &CSEHHandlerDlg::OnCleanOutputBtnClicked)
	
END_MESSAGE_MAP()


// CSEHHandlerDlg message handlers

BOOL CSEHHandlerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	InitExceptionList();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Callback for win32 exceptions
LONG WINAPI CustomUnhandledExceptionFilter( _EXCEPTION_POINTERS* ExceptionInfo )
{
	BOOL createDump = ( ExceptionInfo->ExceptionRecord->ExceptionFlags == 1 ) ? TRUE : FALSE;  
	
	// creating minidump
	if ( createDump )
	{

	}
	else // showing MessageBox with error information
	{
		auto elem = std::find( exceptionDefines.begin(), exceptionDefines.end(),
			ExceptionInfo->ExceptionRecord->ExceptionCode );
		int index = std::distance(exceptionDefines.begin(), elem);

		::MessageBoxW( NULL, exceptionsTypes[index], _T("RaiseException information"), MB_ICONEXCLAMATION | MB_OK );
	}
	return EXCEPTION_EXECUTE_HANDLER;
}


// List all available exceptions to be passed to RaiseException
void CSEHHandlerDlg::InitExceptionList()
{
	for ( auto excElem : exceptionsTypes )
	{
		m_List.AddString(excElem);
	}
}

// Change MiniDump creation flag
void CSEHHandlerDlg::OnMiniDumpBtnClicked()
{
	m_ControlOutput.EnableWindow( m_CreateMiniDump ? FALSE : TRUE );
	m_CreateMiniDump = !m_CreateMiniDump;
}

// Clean output window
void CSEHHandlerDlg::OnCleanOutputBtnClicked()
{
	g_Output.Empty();
	m_ControlOutput.SetWindowText( _T("") );
}

void CSEHHandlerDlg::OnRaiseExceptionBtnClicked()
{
	if ( m_List.GetCurSel() == LB_ERR )
	{
		::MessageBox( NULL, _T("Choose an exception to raise!"), _T("SEH_Handler Error"),   MB_ICONERROR | MB_OK );
		return;
	}

	// Get selected exception DWORD code for RaiseException
	int chosenIdx = m_List.GetCurSel();
	
	
	__try {
		RaiseException( exceptionDefines[chosenIdx], m_CreateMiniDump? 1 : 0, 0, NULL );
	}
	__except( CustomUnhandledExceptionFilter( GetExceptionInformation() ) )
	{

	}

	if ( m_CreateMiniDump )
	{
		
		m_ControlOutput.SetWindowTextW(g_Output);
	}
}
