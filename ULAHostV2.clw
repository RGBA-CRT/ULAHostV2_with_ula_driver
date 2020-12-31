; CLW ÉtÉ@ÉCÉãÇÕ MFC ClassWizard ÇÃèÓïÒÇä‹ÇÒÇ≈Ç¢Ç‹Ç∑ÅB

[General Info]
Version=1
LastClass=CULAHostV2Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ULAHostV2.h"

ClassCount=5
Class1=CULAHostV2App
Class2=CULAHostV2Dlg
Class3=CAboutDlg

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ULAHOSTV2_DIALOG
Resource4=IDD_ABOUTBOX (âpåÍ (±“ÿ∂))
Resource5=IDD_ULA_DIALOG
Resource6=IDD_ULA_TURN_ON_DIALOG (English (U.S.))
Resource7=IDD_ABOUTBOX (English (U.S.))
Class4=CULADialog
Resource8=IDD_ULAHOSTV2_DIALOG (English (U.S.))
Class5=CULATurnOnDlg
Resource9=IDD_ULA_TURN_ON_DIALOG (âpåÍ (±“ÿ∂))
Resource10=IDD_ULAHOSTV2_DIALOG (âpåÍ (±“ÿ∂))

[CLS:CULAHostV2App]
Type=0
HeaderFile=ULAHostV2.h
ImplementationFile=ULAHostV2.cpp
Filter=N

[CLS:CULAHostV2Dlg]
Type=0
HeaderFile=ULAHostV2Dlg.h
ImplementationFile=ULAHostV2Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDCANCEL

[CLS:CAboutDlg]
Type=0
HeaderFile=ULAHostV2Dlg.h
ImplementationFile=ULAHostV2Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_ULAHOSTV2_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CULAHostV2Dlg

[DLG:IDD_ULAHOSTV2_DIALOG (âpåÍ (±“ÿ∂))]
Type=1
Class=CULAHostV2Dlg
ControlCount=7
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BUTTON1,button,1342242944
Control4=IDC_BUTTON2,button,1342242944
Control5=IDC_BUTTON3,button,1342242944
Control6=IDC_BUTTON4,button,1342242944
Control7=IDC_BUTTON5,button,1342242944

[DLG:IDD_ABOUTBOX (âpåÍ (±“ÿ∂))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ULAHOSTV2_DIALOG (English (U.S.))]
Type=1
Class=CULAHostV2Dlg
ControlCount=7
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BUTTON1,button,1342242944
Control4=IDC_BUTTON2,button,1342242944
Control5=IDC_BUTTON3,button,1342242944
Control6=IDC_BUTTON4,button,1342242944
Control7=IDC_BUTTON5,button,1342242944

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CULADialog]
Type=0
HeaderFile=uladialog\uladialog.h
ImplementationFile=uladialog\uladialog.cpp
BaseClass=CDialog
LastObject=CULADialog

[DLG:IDD_ULA_DIALOG]
Type=1
Class=CULADialog
ControlCount=16
Control1=IDOK,button,1208025089
Control2=IDCANCEL,button,1342242816
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_STATIC,static,1342308353
Control5=IDC_STATIC_TRANSFER_VALUE,static,1342308354
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ABORT,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_BACKUP_MEMORY,static,1342308866
Control14=IDC_MEMORYSIZE_STATIC,static,1342177794
Control15=IDC_MEMORYTYPE_STATIC,static,1342308866
Control16=IDC_STATIC,static,1342308353

[CLS:CULATurnOnDlg]
Type=0
HeaderFile=uladialog\ulaturnondlg.h
ImplementationFile=uladialog\ulaturnondlg.cpp
BaseClass=CDialog
LastObject=CULATurnOnDlg

[DLG:IDD_ULA_TURN_ON_DIALOG (âpåÍ (±“ÿ∂))]
Type=1
Class=CULATurnOnDlg
ControlCount=3
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC_TURN_GBA,static,1342308865

[DLG:IDD_ULA_TURN_ON_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC_TURN_GBA,static,1342308865

