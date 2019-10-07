#if !defined(AFX_CLIENTSOCKET_H__CE0F1A43_78EB_11D4_ACB2_00500464FA8A__INCLUDED_)
#define AFX_CLIENTSOCKET_H__CE0F1A43_78EB_11D4_ACB2_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CSockListenerDlg ;

class CClientSocket : public CSocket
{
// Attributes
public:
	CSockListenerDlg *m_ptrDlg;
// Operations
public:
	CClientSocket(CSockListenerDlg *ptrDlg);
	virtual ~CClientSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__CE0F1A43_78EB_11D4_ACB2_00500464FA8A__INCLUDED_)
