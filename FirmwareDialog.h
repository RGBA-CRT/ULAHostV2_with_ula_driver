#pragma once
#include "ula_driver/ula_driver.h"

// FirmwareDialog ダイアログ

class FirmwareDialog : public CDialog {
  DECLARE_DYNAMIC(FirmwareDialog)

private:
  void EnumUsbDevices(CComboBox *cbox);
  uint16_t vid_ = 0, pid_ = 0;

public:
  FirmwareDialog(CWnd *pParent = NULL); // 標準コンストラクタ
  virtual ~FirmwareDialog();

  void GetVidPid(uint16_t *vid, uint16_t *pid);

  // ダイアログ データ
  enum { IDD = IDD_FWDL };

protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV サポート

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnCbnSelchangeCombo1();
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedTransfar();
  afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);

  afx_msg void OnDropFiles(HDROP hDropInfo);
  afx_msg void OnEnChangeFirmpath();
  afx_msg void OnBnClickedConnect();
  afx_msg void OnClose();
  afx_msg BOOL OnInitDialog();
};
