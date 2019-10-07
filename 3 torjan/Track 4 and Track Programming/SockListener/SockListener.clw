; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSockListenerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SockListener.h"

ClassCount=5
Class1=CSockListenerApp
Class2=CSockListenerDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMySocket
Class5=CClientSocket
Resource3=IDD_SOCKLISTENER_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_SOCKLISTENER_DIALOG (English (U.S.))

[CLS:CSockListenerApp]
Type=0
HeaderFile=SockListener.h
ImplementationFile=SockListener.cpp
Filter=N

[CLS:CSockListenerDlg]
Type=0
HeaderFile=SockListenerDlg.h
ImplementationFile=SockListenerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EXIT

[CLS:CAboutDlg]
Type=0
HeaderFile=SockListenerDlg.h
ImplementationFile=SockListenerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SOCKLISTENER_DIALOG]
Type=1
Class=CSockListenerDlg
ControlCount=3
Control1=IDC_EXIT,button,1342242816
Control2=IDC_TEXT,static,1342308353
Control3=IDC_LIST1,listbox,1352728835

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CMySocket

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CClientSocket
VirtualFilter=uq

[DLG:IDD_SOCKLISTENER_DIALOG (English (U.S.))]
Type=1
Class=CSockListenerDlg
ControlCount=3
Control1=IDC_EXIT,button,1342242816
Control2=IDC_TEXT,static,1342308353
Control3=IDC_LIST1,listbox,1352728835

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

