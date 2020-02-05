
// SEH_HandlerDlg.h : header file
//

#pragma once


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
	CString m_EchoText;
	CListBox m_List;
	CButton m_MiniDumpButton;
	// Activation flag for minidump creation
	BOOL m_CreateMiniDump = false;
	 
     CString m_Output;
	CEdit m_ControlOutput;
};
