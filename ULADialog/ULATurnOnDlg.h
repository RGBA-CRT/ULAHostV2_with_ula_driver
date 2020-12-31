#if !defined(AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_)
#define AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ULATurnOnDlg.h : ヘッダー ファイル
//

#include "ULADialogResource.h"

/////////////////////////////////////////////////////////////////////////////
// CULATurnOnDlg ダイアログ

class CULATurnOnDlg : public CDialog
{
// コンストラクション
public:
	void CloseULATurnOnDlg();
	BOOL Create(CWnd *pWnd);
	CWnd * m_pParent;
	CULATurnOnDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CULATurnOnDlg)
//	enum { IDD = IDD_DIALOG1 };
	enum { IDD = IDD_ULA_TURN_ON_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CULATurnOnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CULATurnOnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_)
