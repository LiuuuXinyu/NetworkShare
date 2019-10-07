// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockListener.h"
#include "ClientSocket.h"
#include "SockListenerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket(CSockListenerDlg *ptrDlg)
{
	m_ptrDlg = ptrDlg;
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions

int CClientSocket::Send(const void* lpBuf, int nBufLen, int nFlags) 
{
	
	return CSocket::Send(lpBuf, nBufLen, nFlags);
}

void CClientSocket::OnClose(int nErrorCode) 
{	
	m_ptrDlg->OnCloseConnection(this);	
	CSocket::OnClose(nErrorCode);	
}

void CClientSocket::OnReceive(int nErrorCode) 
{		
	CSocket::OnReceive(nErrorCode);
	m_ptrDlg->ProcessPendingRead(this);	
}
