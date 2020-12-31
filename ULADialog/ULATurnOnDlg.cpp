// ULATurnOnDlg.cpp : インプリメンテーション ファイル
//

#include "..\stdafx.h"
#include "..\ULAHostV2Dlg.h"

#include "ULATurnOnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CULATurnOnDlg ダイアログ


CULATurnOnDlg::CULATurnOnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CULATurnOnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CULATurnOnDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		m_pParent = NULL;
	//}}AFX_DATA_INIT
}


void CULATurnOnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CULATurnOnDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CULATurnOnDlg, CDialog)
	//{{AFX_MSG_MAP(CULATurnOnDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULATurnOnDlg メッセージ ハンドラ

BOOL CULATurnOnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

BOOL CULATurnOnDlg::Create(CWnd *pWnd)
{
    m_pParent = pWnd;
    BOOL bret = CDialog::Create(CULATurnOnDlg::IDD, m_pParent);

    if(bret == TRUE){
        this->ShowWindow(SW_SHOW);
    }
    return bret;
}

void CULATurnOnDlg::PostNcDestroy() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
    if( m_pParent != NULL)
    {
        ((CULAHostV2Dlg *)m_pParent)->EndULATurnOnDlg();
        delete this;
    }
	
	CDialog::PostNcDestroy();
}

void CULATurnOnDlg::OnClose() 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
    if( m_pParent != NULL)
    {
        DestroyWindow();
    }
    else{	
		CDialog::OnClose();
	}
}

void CULATurnOnDlg::CloseULATurnOnDlg()
{
	OnClose();
}
