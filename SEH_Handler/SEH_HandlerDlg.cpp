
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


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSEHHandlerDlg dialog



CSEHHandlerDlg::CSEHHandlerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEH_HANDLER_DIALOG, pParent)
	, m_Output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSEHHandlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EXCEPTIONS_LIST, m_List);
	DDX_Control(pDX, ID_MINIDUMP_BOX, m_MiniDumpButton);
	DDX_Text(pDX, ID_EXCEPTION_RES, m_Output);
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

// List all available exceptions to be passed to RaiseException
void CSEHHandlerDlg::InitExceptionList()
{
	for (auto excElem : exceptionsTypes)
	{
		m_List.AddString(excElem);
	}
}

// Change MiniDump creation flag
void CSEHHandlerDlg::OnMiniDumpBtnClicked()
{
	m_ControlOutput.EnableWindow(m_CreateMiniDump ? FALSE : TRUE);
	m_CreateMiniDump = !m_CreateMiniDump;
}

// Clean output window
void CSEHHandlerDlg::OnCleanOutputBtnClicked()
{
	m_Output.Empty();
	m_ControlOutput.SetWindowText(_T(""));
}

void CSEHHandlerDlg::OnRaiseExceptionBtnClicked()
{
	if ( m_List.GetCurSel() == LB_ERR )
	{
		::MessageBox( NULL, _T("Choose an exception to raise!"), _T("SEH_Handler Error"),   MB_ICONERROR | MB_OK );
		return;
	}

	CString chosenException;
	m_List.GetText(m_List.GetCurSel(), chosenException);

	if(m_CreateMiniDump)
	{
          m_ControlOutput.SetWindowTextW(chosenException);
	}
}

void CSEHHandlerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSEHHandlerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
