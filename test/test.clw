; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=FilesStatus
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "test.h"

ClassCount=4
Class1=CTestApp
Class2=CTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TEST_DIALOG
Class4=FilesStatus
Resource4=IDD_DIALOG_FILES_STATUS

[CLS:CTestApp]
Type=0
HeaderFile=test.h
ImplementationFile=test.cpp
Filter=N

[CLS:CTestDlg]
Type=0
HeaderFile=testDlg.h
ImplementationFile=testDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTestDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=testDlg.h
ImplementationFile=testDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TEST_DIALOG]
Type=1
Class=CTestDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_SELECT_DIR,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_SRC,edit,1350631552

[CLS:FilesStatus]
Type=0
HeaderFile=FilesStatus.h
ImplementationFile=FilesStatus.cpp
BaseClass=CDialog
Filter=D
LastObject=FilesStatus

[DLG:IDD_DIALOG_FILES_STATUS]
Type=1
Class=FilesStatus
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631424

