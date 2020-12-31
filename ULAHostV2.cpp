// ULAHostV2.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "ULAHostV2.h"
#include "ULAHostV2Dlg.h"
#include "FirmwareDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2App

BEGIN_MESSAGE_MAP(CULAHostV2App, CWinApp)
	//{{AFX_MSG_MAP(CULAHostV2App)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2App クラスの構築

CULAHostV2App::CULAHostV2App()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CULAHostV2App オブジェクト

CULAHostV2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2App クラスの初期化

BOOL CULAHostV2App::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	FirmwareDialog fwdlg;
	if (fwdlg.DoModal() != IDOK) {
		return FALSE;
	}
	
	uint16_t vid, pid;
	fwdlg.GetVidPid(&vid, &pid);
	if (vid == 0 && pid == 0) {
		return FALSE;
	}

	CULAHostV2Dlg dlg;
	m_pMainWnd = &dlg;

	dlg.SetDevice(vid, pid);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
