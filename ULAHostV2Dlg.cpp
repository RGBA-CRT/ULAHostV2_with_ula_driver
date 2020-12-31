// ULAHostV2Dlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "ULAHostV2.h"
#include "ULAHostV2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
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
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2Dlg ダイアログ

CULAHostV2Dlg::CULAHostV2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CULAHostV2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CULAHostV2Dlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	bmpPC2GBACART.LoadBitmap(IDB_PC2GBACART);
    bmpPC2CART.LoadBitmap(IDB_PC2CART);
	bmpGBACART2PC.LoadBitmap(IDB_GBACART2PC);
	bmpCART2PC.LoadBitmap(IDB_CART2PC);
	bmpGetCartInfo.LoadBitmap(IDB_CARTINFO);

}

void CULAHostV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CULAHostV2Dlg)
	DDX_Control(pDX, IDC_BUTTON5, m_ctlGetCartInfobtn);
	DDX_Control(pDX, IDC_BUTTON4, m_ctlCART2PCbtn);
	DDX_Control(pDX, IDC_BUTTON3, m_ctlGBACART2PCbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_ctlPC2CARTbtn);
	DDX_Control(pDX, IDC_BUTTON1, m_ctlPC2GBACARTbtn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CULAHostV2Dlg, CDialog)
	//{{AFX_MSG_MAP(CULAHostV2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2Dlg メッセージ ハンドラ

void CULAHostV2Dlg::SetDevice(u16 vid, u16 pid) {
	m_ULADialog.SetDevice(vid, pid);
}

BOOL CULAHostV2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
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
		
	    HBITMAP hbmpPC2GBACART, hbmpPC2CART, hbmpGBACART2PC, hbmpCART2PC, hbmpCARTINFO;

	    hbmpPC2GBACART = HBITMAP(bmpPC2GBACART);
	    hbmpPC2CART = HBITMAP(bmpPC2CART);
		hbmpGBACART2PC  = HBITMAP(bmpGBACART2PC);
		hbmpCART2PC = HBITMAP(bmpCART2PC);
		hbmpCARTINFO = HBITMAP(bmpGetCartInfo);

	    m_ctlPC2GBACARTbtn.SetBitmap(hbmpPC2GBACART);
	    m_ctlPC2CARTbtn.SetBitmap(hbmpPC2CART);
		m_ctlGBACART2PCbtn.SetBitmap(hbmpGBACART2PC);
		m_ctlCART2PCbtn.SetBitmap(hbmpCART2PC);
		m_ctlGetCartInfobtn.SetBitmap(hbmpCARTINFO);

		EnableToolTips(TRUE);

	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	// For ULA handling ...
	char s8TargetDir[512];
	GetCurrentDirectory(sizeof(s8TargetDir), s8TargetDir);
	m_ULADialog.ulaSetTargetDir(s8TargetDir);
	//m_ULADialog.ulaFirmDownload("\\gba_boot.bix");

	m_pULATurnOnDlg = NULL;
	
	if(__argc == 2){
		::Sleep(WAIT_FOR_COMMAND);
		GBASwitch();
		m_ULADialog.ulaStartUpTemp(ULA_PROG_DOWNLOAD, __argv[1]);
		m_pULATurnOnDlg->CloseULATurnOnDlg();
		m_ULADialog.DoModal();
		OnCancel();
	}

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CULAHostV2Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}


void CULAHostV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CULAHostV2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CULAHostV2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CULAHostV2Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(
		TRUE,
		NULL,
		NULL,
		OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_SHOWHELP,
		"GBA binary file (*.gba)|*.gba|Multi Boot Mode (*.mb)|*.mb|PogoShell Image (*.bin)|*.bin||",
		NULL
		);
	if(dialog.DoModal() == IDOK){

		// Prepare CString -> char
		char fileNameBuf[512];
		CString workCStr;

		workCStr = dialog.GetPathName();
		strcpy_s(fileNameBuf, workCStr.GetBuffer(512));


		// Kick ULA !!
		GBASwitch();

//
// Will be removed sync fwlib.bin and gba_boot.bix
//
		int ret = AfxMessageBox("Download to EWRAM of GBA ?", MB_YESNO);
		if(ret == IDYES)
			m_ULADialog.ulaStartUpTemp(ULA_PROG_DOWNLOAD, fileNameBuf);
		else
//
//
// 
			m_ULADialog.ulaStartUp(ULA_PROG_DOWNLOAD, fileNameBuf);

		m_pULATurnOnDlg->CloseULATurnOnDlg();

		m_ULADialog.DoModal();

	}
}

void CULAHostV2Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(
		TRUE,
		NULL,
		NULL,
		OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_SHOWHELP,
		"GBA backup data file (*.sav)|*.sav|Boot chip file (*.gba)|*.gba|Multi Boot Mode (*.mb)|*.mb||",
		NULL
		);
	if(dialog.DoModal() == IDOK){

		// Prepare CString -> char
		char fileNameBuf[512];
		CString workCStr;

		workCStr = dialog.GetPathName();
		strcpy_s(fileNameBuf, workCStr.GetBuffer(512));

		GBASwitch();

		// Kick ULA !!
		m_ULADialog.ulaStartUp(ULA_DATA_DOWNLOAD, fileNameBuf);

		m_pULATurnOnDlg->CloseULATurnOnDlg();

		m_ULADialog.DoModal();

	}	
}

void CULAHostV2Dlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(
		FALSE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		"GBA binary file (*.gba)|*.gba||",
		NULL
		);
	if(dialog.DoModal() == IDOK){

		// Prepare CString -> char
		char fileNameBuf[512];
		CString workCStr;

		workCStr = dialog.GetPathName();
		strcpy_s(fileNameBuf, workCStr.GetBuffer(512));

		GBASwitch();

		// Kick ULA !!
		m_ULADialog.ulaStartUp(ULA_PROG_UPLOAD, fileNameBuf);

		m_pULATurnOnDlg->CloseULATurnOnDlg();

		m_ULADialog.DoModal();

	}
	
}

void CULAHostV2Dlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(
		FALSE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		"GBA backup data file (*.sav)|*.sav||",
		NULL
		);
	if(dialog.DoModal() == IDOK){

		// Prepare CString -> char
		char fileNameBuf[512];
		CString workCStr;

		workCStr = dialog.GetPathName();
		strcpy_s(fileNameBuf, workCStr.GetBuffer(512));

		GBASwitch();

		// Kick ULA !!
		m_ULADialog.ulaStartUp(ULA_DATA_UPLOAD, fileNameBuf);

		m_pULATurnOnDlg->CloseULATurnOnDlg();

		m_ULADialog.DoModal();

	}	
	
}

void CULAHostV2Dlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	
	GBASwitch();

	// Kick ULA !!
	m_ULADialog.ulaStartUp(ULA_GET_CART_INFO, "");

	m_pULATurnOnDlg->CloseULATurnOnDlg();

	m_ULADialog.DoModal();

}

CULAHostV2Dlg::~CULAHostV2Dlg()
{
	bmpPC2GBACART.DeleteObject();
    bmpPC2CART.DeleteObject();
	bmpGBACART2PC.DeleteObject();
	bmpCART2PC.DeleteObject();
	bmpGetCartInfo.DeleteObject();
}

BOOL CULAHostV2Dlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT*)pNMHDR;

	if(pTTT->uFlags & TTF_IDISHWND){
		id = ::GetDlgCtrlID((HWND)pNMHDR->idFrom);
	}
	else{
		id = pNMHDR->idFrom;
	}

	switch(id){
		case IDC_BUTTON1:
			pTTT->lpszText = _T("Download Program to GBA/Flash Cart.");
			pTTT->hinst = NULL;
			break;

		case IDC_BUTTON2:
			pTTT->lpszText = _T("Download Data to Cart.");
			pTTT->hinst = NULL;
			break;

		case IDC_BUTTON3:
			pTTT->lpszText = _T("Upload program from Cart.");
			pTTT->hinst = NULL;
			break;

		case IDC_BUTTON4:
			pTTT->lpszText = _T("Upload data from Cart.");
			pTTT->hinst = NULL;
			break;

		case IDC_BUTTON5:
			pTTT->lpszText = _T("Get Cart Information.");
			pTTT->hinst = NULL;
			break;

		default:
			break;

		return TRUE;
	}

	return FALSE;
}

#define META_CLASS CULAHostV2Dlg
#include ".\\ULADialog\ULATurnOnDialog.c"


void CAboutDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	OnOK();
}
