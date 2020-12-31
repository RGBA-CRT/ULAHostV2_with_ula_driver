// ULAHostV2Dlg.h : ヘッダー ファイル
//

#if !defined(AFX_ULAHOSTV2DLG_H__BF630C3B_05E9_4904_BA89_0809DF09E61E__INCLUDED_)
#define AFX_ULAHOSTV2DLG_H__BF630C3B_05E9_4904_BA89_0809DF09E61E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include ".\\ULADialog\ULADialog.h"
#include ".\\ULADialog\ULATurnOnDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CULAHostV2Dlg ダイアログ

class CULAHostV2Dlg : public CDialog
{
// 構築
public:
	void EndULATurnOnDlg();
	void GBASwitch();
	BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);

	CULAHostV2Dlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	~CULAHostV2Dlg();

// ダイアログ データ
	//{{AFX_DATA(CULAHostV2Dlg)
	enum { IDD = IDD_ULAHOSTV2_DIALOG };
	CButton	m_ctlGetCartInfobtn;
	CButton	m_ctlCART2PCbtn;
	CButton	m_ctlGBACART2PCbtn;
	CButton	m_ctlPC2CARTbtn;
	CButton	m_ctlPC2GBACARTbtn;
	//}}AFX_DATA

	// For using ULA system
	CULADialog m_ULADialog;
	CULATurnOnDlg* m_pULATurnOnDlg;


	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CULAHostV2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL
    CBitmap bmpPC2GBACART;
    CBitmap bmpPC2CART;
	CBitmap bmpGBACART2PC;
	CBitmap bmpCART2PC;
	CBitmap bmpGetCartInfo;


// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CULAHostV2Dlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ULAHOSTV2DLG_H__BF630C3B_05E9_4904_BA89_0809DF09E61E__INCLUDED_)
