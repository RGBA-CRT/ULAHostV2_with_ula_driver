// ULADialog.cpp : implementation file
//

#include "..\StdAfx.h"

#include "ULADialog.h"

#include <winioctl.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys\stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CULADialog dialog

CULADialog::CULADialog(CWnd* pParent /*=NULL*/)
	: CDialog(CULADialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CULADialog)
	//}}AFX_DATA_INIT
	m_pCRC32 = new CCRC32;

	m_pThread = NULL;
	m_bThread = FALSE;
}

CULADialog::~CULADialog()
{
	delete m_pCRC32;
}

void CULADialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CULADialog)
	DDX_Control(pDX, IDCANCEL, m_wndButtonCancel);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgressCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CULADialog, CDialog)
	//{{AFX_MSG_MAP(CULADialog)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CULADialog message handlers

BOOL CULADialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CRect r;
	GetWindowRect(&r);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	m_wndProgressCtrl.SetRange(0, 100);
	m_wndProgressCtrl.SetStep(1);
	m_wndProgressCtrl.SetPos(0);

	m_bThread = TRUE;
	ulaDispCartInfo();

	switch(m_ulaActionMode){
		case ULA_PROG_DOWNLOAD:
			if(ulaProgDownload(m_targetFilename))
				m_pThread = AfxBeginThread(ThreadFuncDownload, this);
			break;
		case ULA_DATA_DOWNLOAD:
			if(m_RamType){
				ulaDataDownloadSet(m_targetFilename);
				m_pThread = AfxBeginThread(ThreadFuncDownload, this);
			}
			else{
				MessageBox("No Cartridge !!", "Project xLA", MB_ICONSTOP);
				OnCancel();
			}
			break;
		case ULA_PROG_UPLOAD:
			if(m_RomType){
				ulaProgUploadSet(m_targetFilename);
				m_pThread = AfxBeginThread(ThreadFuncUpload, this);
			}
			else{
				MessageBox("No Cartridge !!", "Project xLA", MB_ICONSTOP);
				OnCancel();
			}
			break;
		case ULA_DATA_UPLOAD:
			if(m_RamType){
				ulaDataUploadSet(m_targetFilename);
				m_pThread = AfxBeginThread(ThreadFuncUpload, this);
			}
			else{
				MessageBox("No Cartridge !!", "Project xLA", MB_ICONSTOP);
				OnCancel();
			}
			break;
		case ULA_GET_CART_INFO:
			MoveWindow(r.left, r.top, r.Width(), r.Height() / 2, TRUE);

			GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
			break;
		default:
			break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CULADialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	CloseHandle(m_hULA);
	
	CDialog::OnCancel();
}

// --- For Thread Control ---

UINT CULADialog::ThreadFuncDownload(LPVOID pParam)
{
	((CULADialog*)pParam)->ulaDownloadBody();

	return 0;
}

UINT CULADialog::ThreadFuncUpload(LPVOID pParam)
{
	((CULADialog*)pParam)->ulaUploadBody();

	return 0;
}

void CULADialog::OnAbort() 
{
	// TODO: Add your control notification handler code here
	if(!m_pThread){
		return;
	}

	if(m_bThread){
		m_pThread->SuspendThread();
		int ret = AfxMessageBox("Really Abort ?", MB_YESNO);

		if(ret == IDYES){
			m_bThread = FALSE;
			m_pThread->ResumeThread();
		}
		else{
			m_pThread->ResumeThread();
		}
	}
	else
		AfxMessageBox("Abort Soon.");
}


// --- For ULA ---

void CULADialog::ulaSetActionMode(s32 aActionMode)
{
	m_ulaActionMode = aActionMode;
}

void CULADialog::ulaSetTargetFile(char aFileName[])
{
	strcpy(m_targetFilename, aFileName);
}

void CULADialog::ulaSetTargetDir(char aTargetDir[])
{
	strcpy(m_s8TargetDir, aTargetDir);
}


void CULADialog::ulaBulkOutData(char aMsg[], u8 *aData, u32 aDataSize)
{
	m_ret = FALSE;

	m_bulkControl.pipeNum = BULK_OUT_PIPE;
	m_ret = DeviceIoControl(m_hULA,
						IOCTL_EZUSB_BULK_WRITE,
						&m_bulkControl,
						sizeof(BULK_TRANSFER_CONTROL),
						aData,
						aDataSize,
						&m_nbyte,
						NULL);
	if(m_ret == FALSE){
		MessageBox(aMsg, "Project xLA");
		exit (-1);
	}
}

void CULADialog::ulaBulkInData(char aMsg[], u8 *aData, u32 aDataSize)
{
	m_ret = FALSE;

	m_bulkControl.pipeNum = BULK_IN_PIPE;
	m_ret = DeviceIoControl(m_hULA,
						IOCTL_EZUSB_BULK_READ,
						&m_bulkControl,
						sizeof(BULK_TRANSFER_CONTROL),
						aData,
						aDataSize,
						&m_nbyte,
						NULL);
	if(m_ret == FALSE){
		MessageBox(aMsg, "Project xLA", MB_ICONSTOP);
		exit (-1);
	}

}

void CULADialog::ulaInit()
{

	m_hULA = CreateFile("\\\\.\\ezusb-0",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if(m_hULA != INVALID_HANDLE_VALUE){
	}
	else{
		MessageBox("Could not find ULA system !!", "Project xLA", MB_ICONSTOP);
		exit (-1);
	}

	// Target Reset
	ulaSetCommand("ULA RESET error !!", TARGET_INIT, 0, 0, 0);
}

void CULADialog::ulaFirmDownload(char aFirmFileName[])
{
	// For Firmware
	FILE *fFirmware;
	u8 firmBuffer[FIRM_SIZE];
	HANDLE hXLA;
	BOOLEAN ret;
	unsigned long nbyte;
	VENDOR_REQUEST_IN vreq;


	char firmDir[512];

	strcpy(firmDir, m_s8TargetDir);
	strcat(firmDir, aFirmFileName);


	ret = FALSE;

	// xLA Handling
	hXLA = CreateFile("\\\\.\\ezusb-0",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if(hXLA != INVALID_HANDLE_VALUE){
		//
		// Start xLA session
		//

		//
		// BixFile Open and Load Binary Image to Internal memory
		//
		if((fFirmware = fopen(firmDir, "rb")) != NULL){
			fread(firmBuffer, sizeof(char), FIRM_SIZE, fFirmware);
			fclose(fFirmware);
		}
		else{
			MessageBox(aFirmFileName, "Not Found !!", MB_ICONSTOP);
		}

		//
		// Firmware download
		//
		// EZ-USB halt
		vreq.bRequest = 0xA0;
		vreq.wValue = 0x7F92;
		vreq.wIndex = 0x00;
		vreq.wLength = 0x01;
		vreq.bData = 1;
		vreq.direction = 0x00;
		ret = DeviceIoControl(hXLA,
							IOCTL_Ezusb_VENDOR_REQUEST,
							&vreq,
							sizeof(VENDOR_REQUEST_IN),
							NULL,
							0,
							&nbyte,
							NULL);
		if(ret == FALSE){
			MessageBox("EZ-USB halt error !!", "Project xLA", MB_ICONSTOP);
			exit (-1);
		}
		// EZ-USB firmware download
		ret = DeviceIoControl(hXLA,
							IOCTL_Ezusb_ANCHOR_DOWNLOAD,
							firmBuffer,
							FIRM_SIZE,
							NULL,
							0,
							&nbyte,
							NULL);
		if(ret == FALSE){
			MessageBox("EZ-USB Firmware download error !!", "Project xLA", MB_ICONSTOP);
			exit (-1);
		}

		// EZ-USB Run
		vreq.bRequest = 0xA0;
		vreq.wValue = 0x7F92;
		vreq.wIndex = 0x00;
		vreq.wLength = 0x01;
		vreq.bData = 0;
		vreq.direction = 0x00;
		ret = DeviceIoControl(hXLA,
							IOCTL_Ezusb_VENDOR_REQUEST,
							&vreq,
							sizeof(VENDOR_REQUEST_IN),
							NULL,
							0,
							&nbyte,
							NULL);
		if(ret == FALSE){
			MessageBox("EZ-USB run error !!", "Project xLA", MB_ICONSTOP);
			exit (-1);
		}

		CloseHandle(hXLA);
	}
	else{
		MessageBox("Could not find ULA system !!", "Project xLA", MB_ICONSTOP);
		exit (-1);
	}

}

void CULADialog::ulaSilentDownload(char aTargetFileName[])
{
	int i;
	char firmDir[512];

	strcpy(firmDir, m_s8TargetDir);
	strcat(firmDir, aTargetFileName);

	// Get File Size
	if( (m_fh = _open( firmDir, _O_BINARY)) != -1 ){
		m_fileSize = filelength(m_fh);
	}
	else{
		MessageBox(aTargetFileName, "Not Found !!", MB_ICONSTOP);
		exit (-1);
	}

	ulaSetCommand("ULA Size setting error !!", TARGET_DOWNLOAD, 0x02010000, m_fileSize, 0);

	// File Transfer
	m_bufferCount = m_fileSize / BUFF_SIZE;
	for(i = 0;i <= m_bufferCount;i++){
		_read(m_fh, m_u8ULABuffer, BUFF_SIZE);
		ulaBulkOutData("ULA Prog Out error !!", (u8*)m_u8ULABuffer, BUFF_SIZE);
	}
	_close(m_fh);
}
//
//
// Download Program
// 
u32 CULADialog::ulaProgDownload(char aTargetFileName[])
{
	switch (m_RomType){
		case 0:
		case 1:
			ulaProgDownloadSet(aTargetFileName, FWLIB_WRAM_LOADEXEC);
			break;
		case 2:
		case 3:
			ulaProgDownloadSet(aTargetFileName, FWLIB_ROM_BWRITE);
			break;

		default:
			return 0;
			break;
	}
	return 1;
}


void CULADialog::ulaProgDownloadSet(char aTargetFileName[], u8 aTargetMemoryType)
{
	// Get File Size
	if( (m_fh = _open( aTargetFileName, _O_BINARY)) != -1 ){
		m_fileSize = filelength(m_fh);
	}
	else{
		MessageBox(aTargetFileName, "Not Found !!", MB_ICONSTOP);
		exit (-1);
	}

	// Give Transmit Command
	if(aTargetMemoryType == FWLIB_WRAM_LOADEXEC ){
		m_bufferCount = m_fileSize / BUFF_SIZE;
		m_crc32Padding = m_fileSize % BUFF_SIZE;
		if (m_crc32Padding){
			m_bufferCount++;
		}
		m_RepeatBankNum = 1;
				
		ulaSetCommand("ULA Size setting error !!", aTargetMemoryType, m_fileSize, m_fileSize, 0);
	}
	else{
		m_bufferCount = BLOCK_SIZE / BUFF_SIZE;
		m_crc32Count = m_bufferCount;
		m_RepeatBankNum = m_fileSize / BLOCK_SIZE;
		m_crc32Padding = m_fileSize % BLOCK_SIZE;

		if (m_crc32Padding){
			m_RepeatBankNum++;	
		}
	}

	m_TransferBackUpSize = BUFF_SIZE;
	m_last_percent = -1;
	m_RamType = 0;// To avoid enter backUpMemory Handling.
}

void CULADialog::ulaDataDownloadSet(char aTargetFileName[])
{
	// Get File Size
	if( (m_fh = _open( aTargetFileName, _O_BINARY)) != -1 ){
		m_fileSize = filelength(m_fh);
	}
	else{
		MessageBox(aTargetFileName, "Not Found !!", MB_ICONSTOP);
		exit (-1);
	}

	// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M

			if (m_fileSize >= BACK_UP_MEMORY_SIZE){
				m_bufferCount = BACK_UP_MEMORY_SIZE / BUFF_SIZE;
				m_TransferMemorySize = BACK_UP_MEMORY_SIZE;
				m_fileSize = tbl_backUpMemorySize[m_RamType];
			}
			else{
				m_bufferCount = m_fileSize / BUFF_SIZE;
				m_TransferMemorySize = m_fileSize;
			}

			if (m_fileSize > BUFF_SIZE){
				m_TransferBackUpSize = BUFF_SIZE;
			}
			else{
				m_TransferBackUpSize = m_fileSize;
			}

			m_RepeatBankNum = m_fileSize / BACK_UP_MEMORY_SIZE;
			if(m_RepeatBankNum <= 0){
				m_RepeatBankNum ++;
			}

	switch(m_RamType){
		case 3:
		case 6:
			m_bufferCount = m_fileSize / BUFF_SIZE;
			m_RepeatBankNum = 1;
			break;

		default:	
			break;
	}


	m_crc32Count = m_bufferCount;
	m_crc32Padding = m_fileSize % BUFF_SIZE;

	if (m_crc32Padding){
		m_bufferCount++;
	}
	m_last_percent = -1;

}



void CULADialog::ulaDownloadBody()
{
	s32 i, j, k;
	u32 crcrx;
	char msg[128];
	s32 offset = 0;

	for(k = 0;k < m_RepeatBankNum && m_bThread; k++){
		m_pCRC32->initCRC32();
		// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
		switch(m_RamType){
			case 0:
				// Give Transmit Command
				if(m_RomType == 3 ){
					ulaSetCommand("ULA Size setting error !!", FWLIB_ROM_BWRITE, offset, BLOCK_SIZE, 0);
				}
				break;

			case 1: // 32KB and less than 32KB
				ulaSetCommand("ULA Download command error !!", FWLIB_SRAM_WRITE, k, m_TransferMemorySize, 0);
			break;

			case 2: //64KB
				if(k){
					ulaSetCommand("ULA Download command error !!", FWLIB_SRAM2EWRAM, k, 0, 0);
					::Sleep(WAIT_FOR_BACKUP_RAM);
					ulaSetCommand("ULA Download command error !!", FWLIB_WRITE, 0x02018000, BACK_UP_MEMORY_SIZE, 0);
				}
				else{
					ulaSetCommand("ULA Download command error !!", FWLIB_SRAM_WRITE, offset, BACK_UP_MEMORY_SIZE, 0);
				}
				break;

			case 3: // 64KB
				ulaSetCommand("ULA Download command error !!", FWLIB_FLASH_WRITE, offset, m_fileSize, 0);
				break;

			case 4:	// 512B
			case 5: // 8 KB
				ulaSetCommand("ULA Download command error !!", FWLIB_EEP_WRITE, offset, m_fileSize, 0);
				break;

			case 6: // 128KB
				ulaSetCommand("ULA Download command error !!", FWLIB_FLASH_WRITE, offset, m_fileSize, 0);
				break;

			default:
				break;
		}		
		
		
		for(j = 0;j < m_bufferCount && m_bThread; j++){

			_read(m_fh, m_u8ULABuffer, m_TransferBackUpSize);

			switch(m_RamType){
				case 4:
				case 5:
					ulaExchangeForVBA();
					break;
				default:
					break;
			}

			ulaBulkOutData("ULA Download error !!", (u8*)m_u8ULABuffer, m_TransferBackUpSize);

			for(i = 0;i < BUFF_SIZE;i++){
				m_pCRC32->setCRC32(m_pCRC32->getCRC32(m_u8ULABuffer[i]));
			}

			m_now_percent = (j + offset / BUFF_SIZE) * 100 / (m_bufferCount * m_RepeatBankNum) ;
			if( m_last_percent != m_now_percent){
				m_last_percent = m_now_percent;

				// Imp: Progress Bar update
				m_wndProgressCtrl.SetPos(m_now_percent);

				sprintf(msg,"%d", m_now_percent);
				GetDlgItem(IDC_STATIC_TRANSFER_VALUE)->SetWindowText(msg);
				m_wndProgressCtrl.UpdateWindow();
			}
		}

		// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
		switch(m_RamType){
			case 0:
				// Nothing for program downloading !!
				break;
			case 1:
				ulaSetCommand("ULA Download command error !!", FWLIB_EWRAM2SRAM, k, 0, 0);
				::Sleep(WAIT_FOR_BACKUP_RAM);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				break;
		}

		m_pCRC32->setCRC32(~m_pCRC32->getCRC32());

		// CRC32
		switch(m_RomType){
			case 3:
				crcrx = ~ulaCRC32FromGBA();
				if (m_pCRC32->getCRC32() != crcrx){
					sprintf(msg,"CRC %08x %08x", m_pCRC32->getCRC32(), crcrx);
					MessageBox(msg, "Project xLA", MB_ICONSTOP);
				}
				break;
		}
		offset = offset + BLOCK_SIZE;
	}

	switch(m_RomType){
		case 3:
			ulaSetCommand("ULA ROM Boot command error !!", FWLIB_BOOT_ROM, 0, 0, 0);
			break;
	}
	switch(m_RamType){
		case 2:
			ulaSetCommand("ULA Download command error !!", FWLIB_EWRAM2SRAM, k, 0, 0);
	}
	_close(m_fh);

	// Thread Handling
	m_pThread = NULL;
	m_bThread = FALSE;

	::Sleep(WAIT_FOR_BACKUP_RAM);			

	OnCancel();
}

void CULADialog::ulaProgUploadSet(char aTargetFileName[])
{
	// Get File Handler
	if( (m_fh = _open( aTargetFileName, _O_BINARY | _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE)) != -1 ){
	}
	else{
		MessageBox(aTargetFileName, "Not Found !!", MB_ICONSTOP);
		exit (-1);
	}

	ulaSetCommand("ULA Upload command error !!", FWLIB_READ, GBA_CART_ROM_ADDRESS, m_RomSize, 0);

	m_bufferCount = m_RomSize / BUFF_SIZE;

	m_crc32Count = m_bufferCount;
	m_crc32Padding = m_RomSize % BUFF_SIZE;

	if (m_crc32Padding){
		m_bufferCount++;
	}
	m_TransferBackUpSize = BUFF_SIZE;
	m_last_percent = -1;
	m_RepeatBankNum = 1;
	m_RamType = 0;	// To avoid enter backUpMemory Handling.
}

void CULADialog::ulaDataUploadSet(char aTargetFileName[])
{
	if(!m_RomType)
		return;

	// Get File Handler
	if( (m_fh = _open( aTargetFileName, _O_BINARY | _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE)) != -1 ){
	}
	else{
		MessageBox(aTargetFileName, "Not Found !!", MB_ICONSTOP);
		exit (-1);
	}

	// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
	m_fileSize = tbl_backUpMemorySize[m_RamType];
	m_RepeatBankNum = m_fileSize / BACK_UP_MEMORY_SIZE;

	if(m_RepeatBankNum <= 0){
		m_RepeatBankNum ++;
	}

	if (m_fileSize > BACK_UP_MEMORY_SIZE){
		m_bufferCount = BACK_UP_MEMORY_SIZE / BUFF_SIZE;
	}
	else {
		m_bufferCount = m_fileSize / BUFF_SIZE;
	}

	if(m_fileSize < BUFF_SIZE){     
		m_bufferCount = 1;
		m_TransferBackUpSize = m_fileSize;
	}
	else{
		m_TransferBackUpSize = BUFF_SIZE;
	}

	m_crc32Count = m_bufferCount;
	m_crc32Padding = m_RomSize % BUFF_SIZE;

	if (m_crc32Padding){
		m_bufferCount++;
	}
	m_last_percent = -1;

}


void CULADialog::ulaUploadBody()
{
	s32 i, j, k;
	u32 crcrx;
	char msg[128];
	s32 offset = 0;

	for(k = 0;k < m_RepeatBankNum && m_bThread; k++){
		// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
		switch(m_RamType){
			case 0:
				// Do nothing for Program Uploading !!
				break;

			case 1:
				ulaSetCommand("ULA Upload command error !!", FWLIB_SRAM_READ, 0, BACK_UP_MEMORY_SIZE, 0);
				::Sleep(WAIT_FOR_BACKUP_RAM);
				break;

			case 2:
				if(k){
					ulaSetCommand("ULA Upload command error !!", FWLIB_SRAM2EWRAM, k, 0, 0);
					::Sleep(WAIT_FOR_BACKUP_RAM);
					ulaSetCommand("ULA Upload command error !!", FWLIB_READ,0x02018000, BACK_UP_MEMORY_SIZE, 0);
				}
				else{
					ulaSetCommand("ULA Upload command error !!", FWLIB_SRAM_READ, offset, BACK_UP_MEMORY_SIZE, 0);
					::Sleep(WAIT_FOR_BACKUP_RAM);
				}
				break;

			case 3:
				ulaSetCommand("ULA Upload command error !!", FWLIB_SRAM_READ, offset, BACK_UP_MEMORY_SIZE, 0);
				::Sleep(WAIT_FOR_BACKUP_RAM);
				break;

			case 4:
			case 5:
				ulaSetCommand("ULA Upload command error !!", FWLIB_EEP_READ, offset, m_fileSize, 0);
				::Sleep(WAIT_FOR_BACKUP_RAM);
				break;

			case 6:
				ulaSetCommand("ULA Upload command error !!", FWLIB_SRAM_READ, offset, BACK_UP_MEMORY_SIZE, 0);
				::Sleep(WAIT_FOR_BACKUP_RAM);
				break;

			default:
				break;
		}

		for(j = 0;j < m_bufferCount && m_bThread; j++){

			ulaBulkInData("ULA Upload error !!", (u8*)m_u8ULABuffer, m_TransferBackUpSize);

			switch(m_RamType){
				case 4:
				case 5:
					ulaExchangeForVBA();
					break;
				default:
					break;
			}

			_write(m_fh, m_u8ULABuffer, m_TransferBackUpSize);

			for(i = 0;i < BUFF_SIZE;i++){
				if(j < m_crc32Count){
					m_pCRC32->setCRC32(m_pCRC32->getCRC32(m_u8ULABuffer[i]));
				}
			}

			m_now_percent = (j + offset / BUFF_SIZE) * 100 / (m_bufferCount * m_RepeatBankNum) ;
			if( m_last_percent != m_now_percent){
				m_last_percent = m_now_percent;

				// Imp: Progress Bar update
				m_wndProgressCtrl.SetPos(m_now_percent);

				sprintf(msg,"%d", m_now_percent);
				GetDlgItem(IDC_STATIC_TRANSFER_VALUE)->SetWindowText(msg);
				m_wndProgressCtrl.UpdateWindow();
			}
		}

		for(i = 0;i < m_crc32Padding && m_bThread;i++){
			m_pCRC32->setCRC32(m_pCRC32->getCRC32(m_u8ULABuffer[i]));
		}

		m_pCRC32->setCRC32(~m_pCRC32->getCRC32());

		// CRC32
		switch(m_RamType){
			case 0:
				crcrx = ~ulaCRC32FromGBA();
				if (m_pCRC32->getCRC32() != crcrx){
					sprintf(msg,"CRC %08x %08x", m_pCRC32->getCRC32(), crcrx);
					MessageBox(msg, "Project xLA", MB_ICONSTOP);
				}
		}
		offset = offset + BLOCK_SIZE;
	}

	_close(m_fh);

	// Thread Handling
	m_pThread = NULL;
	m_bThread = FALSE;

	OnCancel();
}

void CULADialog::ulaExchangeForVBA()
{
	// data0,1,2,3,4,5,6,7 <-> data7,6,5,4,3,2,1,0
	 
	s32 i, j, k;
	u8  data;

	for(i = 0;i < BUFF_SIZE;i += 8){
		k = 7;
		for(j = 0;j < 4;j++){
			data=m_u8ULABuffer[i + j];
			m_u8ULABuffer[i + j] = m_u8ULABuffer[i + k];
			m_u8ULABuffer[i + k] = data;
			k--;
		}
	}
}




void CULADialog::ulaDispCartInfo()
{
	char msg[128];
	sprintf(msg,"%dMbit", m_RomSize / (1024 * 1024) * 8);
	GetDlgItem(IDC_MEMORYSIZE_STATIC)->SetWindowText(msg);

	GetDlgItem(IDC_MEMORYTYPE_STATIC)->SetWindowText(tbl_memoryType[m_RomType]);
	GetDlgItem(IDC_BACKUP_MEMORY)->SetWindowText(tbl_backUpMemoryType[m_RamType]);

}


u32 CULADialog::ulaCRC32FromGBA()
{
	u32 crc32fromGBA;

	ulaBulkInData("ULA CRC32 response error !!", (u8*)m_u8ULABuffer, RESPONSE_SIZE);

	// CRC32 alignment
	crc32fromGBA = m_u8ULABuffer[3] * 0x1000000 + m_u8ULABuffer[2] * 0x10000 + m_u8ULABuffer[1] * 0x100 + m_u8ULABuffer[0];

	return (~crc32fromGBA);

}

void CULADialog::ulaGetMemoryInfo()
{

	// Get ROM Info
	ulaSetCommand("ULA GetMemoryType command error !!", FWLIB_ROM_PROBE, 0, 0, 0);
	ulaBulkInData("ULA GetMemoryType response error !!", (u8*)m_u8ULABuffer, RESPONSE_SIZE);

	m_RomType = m_u8ULABuffer[3] * 0x1000000 + m_u8ULABuffer[2] * 0x10000 + m_u8ULABuffer[1] * 0x100 + m_u8ULABuffer[0];
	m_RomSize = m_u8ULABuffer[7] * 0x1000000 + m_u8ULABuffer[6] * 0x10000 + m_u8ULABuffer[5] * 0x100 + m_u8ULABuffer[4];
	m_RomBlkSize = m_u8ULABuffer[11] * 0x1000000 + m_u8ULABuffer[10] * 0x10000 + m_u8ULABuffer[9] * 0x100 + m_u8ULABuffer[8];

	// Get RAM Type
	// 0:NONE 1:SRAM256K 2:SRAM512K 3:FLASH512K 4:EEPROM4K 5:EEPROM64K 6:FLASH1M
	ulaSetCommand("ULA GetRAMType command error !!", FWLIB_BU_PROBE, 0, 0, 0);
	ulaBulkInData("ULA GetMemoryType response error !!", (u8*)m_u8ULABuffer, RESPONSE_SIZE);
	m_RamType = m_u8ULABuffer[3] * 0x1000000 + m_u8ULABuffer[2] * 0x10000 + m_u8ULABuffer[1] * 0x100 + m_u8ULABuffer[0];

	// Get Unused size of Cart
	ulaSetCommand("ULA GetMemoryType command error !!", FWLIB_BLANK, 0, 0, 0);
	ulaBulkInData("ULA GetMemoryType response error !!", (u8*)m_u8ULABuffer, RESPONSE_SIZE);
	m_RomUnusedSize = m_u8ULABuffer[3] * 0x1000000 + m_u8ULABuffer[2] * 0x10000 + m_u8ULABuffer[1] * 0x100 + m_u8ULABuffer[0];
}

void CULADialog::ulaStartUp(s32 aActionMode, char aFilename[])
{
	// Common processing
	ulaSetActionMode(aActionMode);
	ulaSetTargetFile(aFilename);
	ulaInit();

	m_pCRC32->initCRC32();

	// From Mootan 16bit type
	ulaSilentDownload("\\fwlib20030312.bin");

	::Sleep(WAIT_FOR_COMMAND);

	ulaGetMemoryInfo();
}

void CULADialog::ulaStartUpTemp(s32 aActionMode, char aFilename[])
{
	// Common processing
	ulaSetActionMode(aActionMode);
	ulaSetTargetFile(aFilename);
	ulaInit();

	m_pCRC32->initCRC32();

	// From Optimize 32bit type
	ulaSilentDownload("\\fwlib.bin");

	::Sleep(WAIT_FOR_COMMAND);

	ulaGetMemoryInfo();
}

void CULADialog::ulaSetCommand(char aMsg[], u8 aCmd, u32 aP1, u32 aP2, u32 aP3)
{
	m_u8ULABuffer[ 0] = aCmd;
	m_u8ULABuffer[ 1] = (u8)(aP1);
	m_u8ULABuffer[ 2] = (u8)(aP1 >>  8);
	m_u8ULABuffer[ 3] = (u8)(aP1 >> 16);
	m_u8ULABuffer[ 4] = (u8)(aP1 >> 24);

	m_u8ULABuffer[ 5] = (u8)(aP2);
	m_u8ULABuffer[ 6] = (u8)(aP2 >>  8);
	m_u8ULABuffer[ 7] = (u8)(aP2 >> 16);
	m_u8ULABuffer[ 8] = (u8)(aP2 >> 24);

	m_u8ULABuffer[ 9] = (u8)(aP3);
	m_u8ULABuffer[10] = (u8)(aP3 >>  8);
	m_u8ULABuffer[11] = (u8)(aP3 >> 16);
	m_u8ULABuffer[12] = (u8)(aP3 >> 24);

	m_ret = FALSE;
	m_bulkControl.pipeNum = BULK_OUT_PIPE;
	m_ret = DeviceIoControl(m_hULA,
						IOCTL_EZUSB_BULK_WRITE,
						&m_bulkControl,
						sizeof(BULK_TRANSFER_CONTROL),
						&m_u8ULABuffer,
						COMMAND_SIZE,
						&m_nbyte,
						NULL);
	if(m_ret == FALSE){
		MessageBox(aMsg, "Project xLA");
		exit (-1);
	}

	::Sleep(WAIT_FOR_COMMAND);
}

// EOF
