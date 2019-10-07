#if !defined(AFX_COMMANDSOCKET_H__C36C8423_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
#define AFX_COMMANDSOCKET_H__C36C8423_7998_11D4_ACB3_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCommandSocket command target

class CSockCommanderDlg;

class CCommandSocket : public CSocket
{
// Attributes
public:
	CSockCommanderDlg *m_ptrDlg;
// Operations
public:
	CCommandSocket(CSockCommanderDlg *ptrDlg);
	virtual ~CCommandSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCommandSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDSOCKET_H__C36C8423_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
