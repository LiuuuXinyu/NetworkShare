// CommandSocket.cpp : implementation file
//

#include "stdafx.h"
#include "SockCommander.h"
#include "CommandSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandSocket

CCommandSocket::CCommandSocket(CSockCommanderDlg *ptrDlg)
{
	m_ptrDlg = m_ptrDlg;
}

CCommandSocket::~CCommandSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCommandSocket, CSocket)
	//{{AFX_MSG_MAP(CCommandSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCommandSocket member functions
