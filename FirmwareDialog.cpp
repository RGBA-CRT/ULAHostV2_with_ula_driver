// FirmwareDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ULAHostV2.h"
#include "FirmwareDialog.h"

#include <setupapi.h>
#include <string>

#define EZUSB_FIRMWARE_NAME "gba_boot.bix"

// FirmwareDialog �_�C�A���O

IMPLEMENT_DYNAMIC(FirmwareDialog, CDialog)

FirmwareDialog::FirmwareDialog(CWnd *pParent /*=NULL*/)
    : CDialog(FirmwareDialog::IDD, pParent) {}

FirmwareDialog::~FirmwareDialog() {}

void FirmwareDialog::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(FirmwareDialog, CDialog)
ON_BN_CLICKED(IDCANCEL, &FirmwareDialog::OnBnClickedCancel)
ON_WM_CREATE()
ON_CBN_SELCHANGE(IDC_COMBO1, &FirmwareDialog::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDOK, &FirmwareDialog::OnBnClickedOk)
ON_BN_CLICKED(IDTRANSFAR, &FirmwareDialog::OnBnClickedTransfar)
//	ON_WM_DEVMODECHANGE()
ON_WM_DEVICECHANGE()
ON_WM_DROPFILES()
ON_EN_CHANGE(IDC_FIRMPATH, &FirmwareDialog::OnEnChangeFirmpath)
ON_BN_CLICKED(IDCONNECT, &FirmwareDialog::OnBnClickedConnect)
ON_WM_CLOSE()
END_MESSAGE_MAP()

// FirmwareDialog ���b�Z�[�W �n���h��

void FirmwareDialog::OnBnClickedCancel() { this->CloseWindow(); }

extern "C" {
void ULA_CALLTYPE EnumDeviceCallback(uint16_t vid, uint16_t pid,
                                     const char *desc, void *userdata) {
  char display_name[100];
  sprintf_s(display_name, "[%04X,%04X] %s", vid, pid, desc);

  CComboBox *cbox = (CComboBox *)userdata;
  cbox->AddString(display_name);
  cbox->SetCurSel(0);
}
}

int FirmwareDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CDialog::OnCreate(lpCreateStruct) == -1)
    return -1;

  return 0;
}

bool ParseUsbDeviceId(char *device_id, size_t id_len, uint16_t *vid,
                      uint16_t *pid) {
  // Todo: �G���[����
  size_t check_len = id_len < 4 ? id_len : id_len - 4;
  for (size_t i = 0; i < check_len; i++) {
    if (device_id[i] == 'V') {
      if (strncmp(&device_id[i], "VID_", 4) == 0) {
        i += 4;
        long num = strtol(&device_id[i], NULL, 16);
        *vid = static_cast<uint16_t>(num);
      }
    } else if (device_id[i] == 'P') {
      if (strncmp(&device_id[i], "PID_", 4) == 0) {
        i += 4;
        long num = strtol(&device_id[i], NULL, 16);
        *pid = static_cast<uint16_t>(num);
      }
    }
  }
  return true;
}

void FirmwareDialog::EnumUsbDevices(CComboBox *cbox) {
  cbox->ResetContent();

  GUID classGUID[1];
  SP_DEVINFO_DATA DeviceInfoData;
  DWORD dwReqSize;

  DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
  if (!SetupDiClassGuidsFromName("USBDevice", classGUID, 1, &dwReqSize)) {
    goto FDEUD_ERROR;
  }

  HANDLE hDevInfoSet =
      SetupDiGetClassDevs(classGUID, NULL, NULL, DIGCF_PRESENT | DIGCF_PROFILE);
  if (hDevInfoSet == INVALID_HANDLE_VALUE) {
    goto FDEUD_ERROR;
  }

  int EnumDeviceIndex = 0;

  while (SetupDiEnumDeviceInfo(hDevInfoSet, EnumDeviceIndex, &DeviceInfoData)) {
    DWORD dwPropType;

    char friendly_name[MAX_PATH];
    if (!SetupDiGetDeviceRegistryProperty(
            hDevInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, &dwPropType,
            reinterpret_cast<PBYTE>(friendly_name), sizeof(friendly_name),
            &dwReqSize))
      continue;

    char port_name[MAX_PATH];
    if (!SetupDiGetDeviceRegistryProperty(
            hDevInfoSet, &DeviceInfoData, SPDRP_HARDWAREID, &dwPropType,
            reinterpret_cast<PBYTE>(port_name), sizeof(port_name), &dwReqSize))
      continue;

    uint16_t vid = 0, pid = 0;
    ParseUsbDeviceId(port_name, sizeof(port_name), &vid, &pid);

    char buf[MAX_PATH * 2 + 32];
    sprintf_s(buf, sizeof(buf), "[%04x:%04x] %s (%s)", vid, pid, friendly_name,
              port_name);
    // sprintf_s(buf, sizeof(buf), "%s (%s)", regFriendlyName, port_name);

    int idx = cbox->AddString(buf);

    uint32_t devid = vid << 16 | pid;
    cbox->SetItemData(idx, devid);

    EnumDeviceIndex++;
  }

  if (EnumDeviceIndex == 0) {
    cbox->AddString("<none>");
    cbox->SetItemData(0, 0);
  }

  cbox->SetCurSel(0);

  return;

FDEUD_ERROR:
  cbox->AddString("Device enum failed.");
  return;
}

BOOL FirmwareDialog::OnInitDialog() {
  CComboBox *cbox = (CComboBox *)this->GetDlgItem(IDC_COMBO1);

  // ula_enum_devices(EnumDeviceCallback, cbox);
  EnumUsbDevices(cbox);

  CEdit *path = (CEdit *)this->GetDlgItem(IDC_FIRMPATH);
  path->SetWindowText(EZUSB_FIRMWARE_NAME);

  return 0;
}

void FirmwareDialog::OnCbnSelchangeCombo1() {
  // TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
}

void FirmwareDialog::OnBnClickedOk() {
  // TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
  CDialog::OnOK();
}

void FirmwareDialog::OnBnClickedTransfar() {
  CComboBox *cbox = (CComboBox *)this->GetDlgItem(IDC_COMBO1);
  int idx = cbox->GetCurSel();
  uint32_t devid = cbox->GetItemData(idx);
  if (devid == 0 || devid == CB_ERR) {
    MessageBox("Error: Device not selected.", 0, MB_ICONERROR);
    return;
  }

  uint16_t vid = devid >> 16;
  uint16_t pid = devid & 0xFFFF;

  CString ezusb_firmware_name;
  CEdit *path = (CEdit *)this->GetDlgItem(IDC_FIRMPATH);
  path->GetWindowText(ezusb_firmware_name);

  FILE *infile = fopen(ezusb_firmware_name, "rb");
  if (infile == NULL) {
    MessageBox("Error: firmware file open error.", 0, MB_ICONERROR);
    return;
  }

  struct stat infile_stat;
  stat(EZUSB_FIRMWARE_NAME, &infile_stat);

  size_t len = infile_stat.st_size;

  uint8_t *fw = new uint8_t[len];
  fread(fw, 1, len, infile);

  bool ret = ula_ezusb_firmware_download(vid, pid, fw, len);
  delete fw;

  if (!ret) {
    MessageBox("Error: fimware download failed.", 0, MB_ICONERROR);
    return;
  }

  MessageBox("The firmware has been transferred successfully.", 0,
             MB_ICONINFORMATION);

  return;
}

BOOL FirmwareDialog::OnDeviceChange(UINT nEventType, DWORD_PTR dwData) {
  CComboBox *cbox = (CComboBox *)this->GetDlgItem(IDC_COMBO1);
  EnumUsbDevices(cbox);

  return TRUE;
}

void FirmwareDialog::OnDropFiles(HDROP hDropInfo) {
  // TODO: �����Ƀ��b�Z�[�W �n���h���[
  // �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

  CDialog::OnDropFiles(hDropInfo);

  char dropfile[MAX_PATH];
  if (DragQueryFile(hDropInfo, 0, dropfile, sizeof(dropfile)) == 0) {
    return;
  }
  DragFinish(hDropInfo);

  CEdit *path = (CEdit *)this->GetDlgItem(IDC_FIRMPATH);
  path->SetWindowText(dropfile);
}

void FirmwareDialog::OnEnChangeFirmpath() {
  // TODO: ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A���̃R���g���[����
  // ���̒ʒm�𑗐M����ɂ́ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���A
  // CRichEditCtrl().SetEventMask() ���֐����Ăяo���܂��B
  // OR ��Ԃ� ENM_CHANGE �t���O���}�X�N�ɓ���ČĂяo���K�v������܂��B

  // TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����Ă��������B
}

void FirmwareDialog::OnBnClickedConnect() {
  CComboBox *cbox = (CComboBox *)this->GetDlgItem(IDC_COMBO1);
  int idx = cbox->GetCurSel();
  uint32_t devid = cbox->GetItemData(idx);
  if (devid == 0 || devid == CB_ERR) {
    MessageBox("Error: Device not selected.", 0, MB_ICONERROR);
    return;
  }

  vid_ = devid >> 16;
  pid_ = devid & 0xFFFF;

  EndDialog(IDOK);
}

void FirmwareDialog::OnClose() {
  CDialog::OnClose();

  EndDialog(IDCANCEL);
}

void FirmwareDialog::GetVidPid(uint16_t *vid, uint16_t *pid) {
  *vid = vid_;
  *pid = pid_;
}