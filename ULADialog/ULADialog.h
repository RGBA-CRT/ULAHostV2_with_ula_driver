#if !defined(AFX_ULADIALOG_H__96A68EB1_B74D_46BD_98EB_FD79CDAEBF45__INCLUDED_)
#define AFX_ULADIALOG_H__96A68EB1_B74D_46BD_98EB_FD79CDAEBF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ULADialog.h : header file
//

#include "ULADialogResource.h"

#include "TYPE.H"
#include "ezusbsys.h"
#include "target_cmd.h"
#include "../ula_driver/ula_driver.h"

#include "CRC32.h"

#define BUFF_SIZE	1024
#define BLOCK_SIZE	32768

#define WAIT_FOR_COMMAND	200
#define WAIT_FOR_BACKUP_RAM	1000
#define BACK_UP_MEMORY_SIZE	0x8000

#define FIRM_SIZE	8192

#define BULK_IN_PIPE 2
#define BULK_OUT_PIPE 3

#define ULA_PROG_DOWNLOAD	1
#define ULA_DATA_DOWNLOAD	2
#define ULA_PROG_UPLOAD		3
#define ULA_DATA_UPLOAD		4
#define ULA_GET_CART_INFO	5

#define ULA_BACK_UP_MEMORY_TYPE 8
#define ULA_CART_MEMORY_TYPE 8

#define LATEST_FIRMZ	0
#define EMBEDDED_FIRMZ	0

/////////////////////////////////////////////////////////////////////////////
// CULADialog dialog

// SetUp Strings
static char* tbl_backUpMemoryType[ULA_BACK_UP_MEMORY_TYPE] = {
	"NONE", "SRAM 256K", "SRAM 512K", "FLASH 512K", "EEPROM 4K", "EEPROM 64K", "FLASH 1M", "????"
};

static char* tbl_memoryType[ULA_CART_MEMORY_TYPE] = {
	"EWRAM", "MASK ROM", "FLASH ROM", "FLASH ROM", "ID-4", "ID-5", "ID-6", "ID-7"
};

// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
static u32 tbl_backUpMemorySize[ULA_BACK_UP_MEMORY_TYPE] = {
	0x0000, 0x8000, 0x10000, 0x10000, 0x0100, 0x2000, 0x20000, 0x0000
};

class CULADialog : public CDialog
{
// Construction
public:
	void SetDevice(u16 vid, u16 pid);

	void ulaStartUp(s32 aActionMode, char aFileName[]);
	void ulaStartUpTemp(s32 aActionMode, char aFileName[]);
	void ulaSetTargetDir(char aTargetDir[512]);
	void ulaGetMemoryInfo();
	u32 ulaCRC32FromGBA();

	u32 ulaProgDownload(char aTargetFileName[512]);
	void ulaProgDownloadSet(char aTargetFileName[512], u8 aTargetMemoryType);
	void ulaDataDownloadSet(char aTargetFileName[512]);
	void ulaDownloadBody();

	void ulaProgUploadSet(char aTargetFileName[512]);
	void ulaDataUploadSet(char aTargetFileName[512]);
	void ulaUploadBody();

	void ulaSilentDownload(char aTargetFileName[512]);
	void ulaFirmDownload(char aFirmFileName[512]);
	void ulaInit();
	CULADialog(CWnd* pParent = NULL);   // standard constructor
	~CULADialog();

	void ulaSetActionMode(s32 aActionMode);
	void ulaSetTargetFile(char aFileName[512]);
	void ulaExchangeForVBA();
	void ulaDispCartInfo();

	// --- For Thread Control ---
	static UINT ThreadFuncDownload(LPVOID pParam);
	static UINT ThreadFuncUpload(LPVOID pParam);

// Dialog Data
	//{{AFX_DATA(CULADialog)
	enum { IDD = IDD_ULA_DIALOG };
	CButton	m_wndButtonCancel;
	CProgressCtrl	m_wndProgressCtrl;
	//}}AFX_DATA
	CCRC32 *m_pCRC32;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CULADialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// --- For Thread Control ---
	BOOL m_bThread;
	CWinThread* m_pThread;

	// Generated message map functions
	//{{AFX_MSG(CULADialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnAbort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ulaSetCommand(char aMsg[512], u8 aCmd, u32 p1, u32 p2, u32 p3);
	void ulaBulkOutData(char aMsg[512], u8 *aData, u32 aDataSize);
	void ulaBulkInData(char aMsg[], u8 *aData, u32 aDataSize);

	s32 m_ulaActionMode;
	char m_targetFilename[512];

	char m_s8TargetDir[512];

	u8 m_u8ULABuffer[BUFF_SIZE];

	// USB handling
	//HANDLE m_hULA;
	unsigned long m_nbyte;
	BOOLEAN m_ret;
	//BULK_TRANSFER_CONTROL m_bulkControl;


	// File handling
	s32 m_fh;
	s32 m_fileSize;
	long m_bufferCount;
	long m_crc32Count, m_crc32Padding;
	s32 m_last_percent, m_now_percent;

	// ROM/RAM handling
	s32 m_RamType;
	u32 m_RamSize;
	s32 m_RomType;
	u32 m_RomSize;
	u32 m_RomBlkSize;
	u32 m_RomUnusedSize;
	s32 m_RepeatBankNum;
	u32 m_TransferMemorySize;
	u32 m_TransferBackUpSize;

	s32 m_tbl_backUpMemorySize[16];

	afx_msg void OnBnClickedCancel();

	u16 m_vid, m_pid;
	ula_handle_t m_ula_handle;
public:
	afx_msg void OnDestroy();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULADIALOG_H__96A68EB1_B74D_46BD_98EB_FD79CDAEBF45__INCLUDED_)
