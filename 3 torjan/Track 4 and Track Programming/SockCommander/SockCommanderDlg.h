// SockCommanderDlg.h : header file
//

#if !defined(AFX_SOCKCOMMANDERDLG_H__C36C841B_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
#define AFX_SOCKCOMMANDERDLG_H__C36C841B_7998_11D4_ACB3_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSockCommanderDlg dialog
#include "CommandSocket.h" 

class CSockCommanderDlg : public CDialog
{
// Construction
	CCommandSocket *m_ptrComSocket;
public:
	BOOL ReceiveResult(CString strCommand);
	BOOL ReceiveFile(CString csMsg, CString csFileName);
	void CheckRegistry();
	CSockCommanderDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL m_nConnected;
// Dialog Data
	//{{AFX_DATA(CSockCommanderDlg)
	enum { IDD = IDD_SOCKCOMMANDER_DIALOG };
	CProgressCtrl	m_progress;
	CString	m_ip;
	CString	m_msg;
	CString	m_port;
	CString	m_csFname;
	CString	m_csCommanderPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockCommanderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSockCommanderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	afx_msg void OnDisconnect();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKCOMMANDERDLG_H__C36C841B_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
