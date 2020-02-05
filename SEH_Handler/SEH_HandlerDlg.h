
// SEH_HandlerDlg.h : header file
//

#pragma once
#define EXCEPTION_MAX_LENGTH 40

const std::vector<TCHAR*> exceptionsTypes = {
	_T("EXCEPTION_ACCESS_VIOLATION"),
	_T("EXCEPTION_ARRAY_BOUNDS_EXCEEDED"),
	_T("EXCEPTION_BREAKPOINT"),
	_T("EXCEPTION_DATATYPE_MISALIGNMENT"),
	_T("EXCEPTION_FLT_DENORMAL_OPERAND"),
	_T("EXCEPTION_FLT_DIVIDE_BY_ZERO"),
	_T("EXCEPTION_FLT_INEXACT_RESULT"),
	_T("EXCEPTION_FLT_INVALID_OPERATION"),
	_T("EXCEPTION_FLT_OVERFLOW"),
	_T("EXCEPTION_FLT_STACK_CHECK"),
	_T("EXCEPTION_FLT_UNDERFLOW"),
	_T("EXCEPTION_GUARD_PAGE"),
	_T("EXCEPTION_ILLEGAL_INSTRUCTION"),
	_T("EXCEPTION_IN_PAGE_ERROR"),
	_T("EXCEPTION_INT_DIVIDE_BY_ZERO"),
	_T("EXCEPTION_INT_OVERFLOW"),
	_T("EXCEPTION_INVALID_DISPOSITION"),
	_T("EXCEPTION_INVALID_HANDLE"),
	_T("EXCEPTION_NONCONTINUABLE_EXCEPTION"),
	_T("EXCEPTION_PRIV_INSTRUCTION"),
	_T("EXCEPTION_SINGLE_STEP"),
	_T("EXCEPTION_STACK_OVERFLOW"),
	_T("STATUS_UNWIND_CONSOLIDATE")
};

// CSEHHandlerDlg dialog
class CSEHHandlerDlg : public CDialogEx
{
// Construction
public:
	CSEHHandlerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEH_HANDLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
	void InitExceptionList();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	// Custom message map functions
	afx_msg void OnMiniDumpBtnClicked();
	afx_msg void OnRaiseExceptionBtnClicked();
	afx_msg void OnCleanOutputBtnClicked();

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_List;

	// Activation flag for minidump creation
	CButton m_MiniDumpButton;
	BOOL m_CreateMiniDump = false;
	
	// Value + Control variables for EditText, where minidump will be printed
     CString m_Output;
	CEdit m_ControlOutput;
};
