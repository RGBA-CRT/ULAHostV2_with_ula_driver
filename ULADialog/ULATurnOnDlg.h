#if !defined(AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_)
#define AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ULATurnOnDlg.h : �w�b�_�[ �t�@�C��
//

#include "ULADialogResource.h"

/////////////////////////////////////////////////////////////////////////////
// CULATurnOnDlg �_�C�A���O

class CULATurnOnDlg : public CDialog
{
// �R���X�g���N�V����
public:
	void CloseULATurnOnDlg();
	BOOL Create(CWnd *pWnd);
	CWnd * m_pParent;
	CULATurnOnDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CULATurnOnDlg)
//	enum { IDD = IDD_DIALOG1 };
	enum { IDD = IDD_ULA_TURN_ON_DIALOG };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CULATurnOnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CULATurnOnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ULATURNONDLG_H__F7D3E372_8D35_4E37_967D_0B947E4FE91C__INCLUDED_)
