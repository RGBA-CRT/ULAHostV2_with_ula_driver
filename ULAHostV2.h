// ULAHostV2.h : ULAHOSTV2 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_)
#define AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��



/////////////////////////////////////////////////////////////////////////////
// CULAHostV2App:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� ULAHostV2.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CULAHostV2App : public CWinApp
{
public:
	CULAHostV2App();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CULAHostV2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CULAHostV2App)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ULAHOSTV2_H__E973BCB4_E84C_4D94_A4C4_E7E77DAC4498__INCLUDED_)
