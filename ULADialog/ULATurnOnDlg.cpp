// ULATurnOnDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CULATurnOnDlg �_�C�A���O


CULATurnOnDlg::CULATurnOnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CULATurnOnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CULATurnOnDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		m_pParent = NULL;
	//}}AFX_DATA_INIT
}


void CULATurnOnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CULATurnOnDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CULATurnOnDlg, CDialog)
	//{{AFX_MSG_MAP(CULATurnOnDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULATurnOnDlg ���b�Z�[�W �n���h��

BOOL CULATurnOnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
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
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
    if( m_pParent != NULL)
    {
        ((CULAHostV2Dlg *)m_pParent)->EndULATurnOnDlg();
        delete this;
    }
	
	CDialog::PostNcDestroy();
}

void CULATurnOnDlg::OnClose() 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
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
