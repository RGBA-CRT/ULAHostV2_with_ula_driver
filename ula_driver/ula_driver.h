#ifndef _ULA_DRIVER_H
#define _ULA_DRIVER_H


#include <libusb-1.0/libusb.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define ULA_BULK_OUT_EP 0x04
#define ULA_BULK_IN_EP 0x83
#define ULA_EZFW_TARGET_INIT 0xFF
#define ULA_EZFW_TARGET_DOWNLOAD 0x00
#define ULA_CMD_WAIT_MS 0x200

#define STRING_DESCRIPTOR_LEN 128
#define ULA_CALLTYPE __stdcall
#ifdef __cplusplus
#define DllExternC extern "C" 
#else
#define DllExternC
#endif
#ifdef ULA_BUILD_DRIVER
#define DllDirection __declspec(dllexport)
#else
#define DllDirection __declspec(dllimport)
#endif

#define DllPublic DllExternC DllDirection

typedef struct {
  libusb_device_handle *libusb_handle;
  uint8_t bluk_out_endpoint;
  uint8_t bluk_in_endpoint;
} ula_handle_internal;

typedef ula_handle_internal *ula_handle_t;
DllPublic bool ULA_CALLTYPE ula_open(ula_handle_t *device, uint16_t vid, uint16_t pid);
DllPublic bool ULA_CALLTYPE ula_close(ula_handle_t device);
DllPublic bool ULA_CALLTYPE ula_set_endpoint(ula_handle_t device, uint8_t bluk_in,
                                   uint8_t bluk_out);

DllPublic bool ULA_CALLTYPE ula_ezusb_firmware_download(uint16_t vid, uint16_t pid,
                                              uint8_t *fw, size_t len);

DllPublic bool ULA_CALLTYPE ula_send_command(ula_handle_t device, uint8_t command,
                                   uint32_t param1, uint32_t param2,
                                   uint32_t param3);

DllPublic bool ULA_CALLTYPE ula_gba_init(ula_handle_t device);

DllPublic void ULA_CALLTYPE ula_sleep_ms(uint32_t ms);

DllPublic bool ULA_CALLTYPE ula_gba_firmware_download(ula_handle_t device,
                                            uint8_t *gba_fw, size_t len);

DllPublic bool ULA_CALLTYPE ula_data_out(ula_handle_t device, uint8_t *data, size_t len);
DllPublic bool ULA_CALLTYPE ula_data_in(ula_handle_t device, uint8_t *data, size_t len,
                              size_t *readsize);

typedef void (* ULA_CALLTYPE ula_enum_devices_callback_t)(uint16_t vid,
                                                         uint16_t pid,
                                                         const char *desc,
                                                         void *userdata);
DllPublic void ULA_CALLTYPE ula_enum_devices(ula_enum_devices_callback_t callback,
                                   void *userdata);

#endif