; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSockCommanderDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SockCommander.h"

ClassCount=4
Class1=CSockCommanderApp
Class2=CSockCommanderDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CCommandSocket
Resource3=IDD_SOCKCOMMANDER_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_SOCKCOMMANDER_DIALOG (English (U.S.))

[CLS:CSockCommanderApp]
Type=0
HeaderFile=SockCommander.h
ImplementationFile=SockCommander.cpp
Filter=N

[CLS:CSockCommanderDlg]
Type=0
HeaderFile=SockCommanderDlg.h
ImplementationFile=SockCommanderDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_FNAME

[CLS:CAboutDlg]
Type=0
HeaderFile=SockCommanderDlg.h
ImplementationFile=SockCommanderDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT2

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_EDIT2,edit,1353783492

[DLG:IDD_SOCKCOMMANDER_DIALOG]
Type=1
Class=CSockCommanderDlg
ControlCount=16
Control1=IDC_IP,edit,1350631552
Control2=IDC_PORT,edit,1350631552
Control3=IDC_MSG,edit,1350631552
Control4=IDC_FNAME,edit,1350631552
Control5=IDC_CONNECT,button,1342242816
Control6=IDC_SEND,button,1342242816
Control7=IDC_DISCONNECT,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TEXT,static,1342308353
Control13=IDC_STATIC,static,1342308352
Control14=IDC_PROGRESS1,msctls_progress32,1082130432
Control15=IDC_COMMANDER_PORT,edit,1484849280
Control16=IDC_STATIC,static,1342308352

[CLS:CCommandSocket]
Type=0
HeaderFile=CommandSocket.h
ImplementationFile=CommandSocket.cpp
BaseClass=CSocket
Filter=N

[DLG:IDD_SOCKCOMMANDER_DIALOG (English (U.S.))]
Type=1
Class=CSockCommanderDlg
ControlCount=16
Control1=IDC_IP,edit,1350631552
Control2=IDC_PORT,edit,1350631552
Control3=IDC_MSG,edit,1350631552
Control4=IDC_FNAME,edit,1350631552
Control5=IDC_CONNECT,button,1342242816
Control6=IDC_SEND,button,1342242816
Control7=IDC_DISCONNECT,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TEXT,static,1342308353
Control13=IDC_STATIC,static,1342308352
Control14=IDC_PROGRESS1,msctls_progress32,1082130432
Control15=IDC_COMMANDER_PORT,edit,1484849280
Control16=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_EDIT2,edit,1353783492

