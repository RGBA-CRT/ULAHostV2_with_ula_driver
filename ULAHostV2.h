// ULAHostV2.h : ULAHOSTV2 アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_)
#define AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル



/////////////////////////////////////////////////////////////////////////////
// CULAHostV2App:
// このクラスの動作の定義に関しては ULAHostV2.cpp ファイルを参照してください。
//

class CULAHostV2App : public CWinApp
{
public:
	CULAHostV2App();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CULAHostV2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CULAHostV2App)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_)
