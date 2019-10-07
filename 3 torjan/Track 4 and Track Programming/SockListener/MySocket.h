#if !defined(AFX_MYSOCKET_H__8B692C95_78D8_11D4_ACB2_00500464FA8A__INCLUDED_)
#define AFX_MYSOCKET_H__8B692C95_78D8_11D4_ACB2_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CMySocket command target
//the listening socket
class CSockListenerDlg ;

class CMySocket : public CSocket
{
// Attributes
public:
	CSockListenerDlg *m_ptrDlg;
// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual BOOL OnMessagePending();
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__8B692C95_78D8_11D4_ACB2_00500464FA8A__INCLUDED_)
