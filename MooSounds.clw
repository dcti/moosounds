; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSystemTrayApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "moosounds.h"
LastPage=0

ClassCount=3
Class1=CMainFrame
Class2=CSystemTrayApp
Class3=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDR_POPUP_MENU
Resource3=IDD_ABOUTBOX

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSystemTrayApp]
Type=0
BaseClass=CWinApp
HeaderFile=MooSounds.h
ImplementationFile=MooSounds.cpp
Filter=N
LastObject=CSystemTrayApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MooSounds.cpp
ImplementationFile=MooSounds.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_APP_ABOUT
Command2=ID_APP_EXIT
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

