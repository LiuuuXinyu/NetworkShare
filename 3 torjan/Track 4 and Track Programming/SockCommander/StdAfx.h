// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C36C841D_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
#define AFX_STDAFX_H__C36C841D_7998_11D4_ACB3_00500464FA8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

#define PORT 888
#define MSG_SOCKET_CREAT_FAIL "Socket Creation Failed."
#define MSG_SOCKET_CONCT_FAIL "Socket Connection Failed."
#define MSG_SOCKET_SEND_FAIL  "Socket Send Failed."
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C36C841D_7998_11D4_ACB3_00500464FA8A__INCLUDED_)
