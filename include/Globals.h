#ifndef GLOBALS_H
#define GLOBALS_H

#include "Secure.h"
//#include "SecureExample.h"
#include <RemoteDebug.h>

// Remote debug instance
#define HOST_NAME "demo"
extern RemoteDebug Debug;

// Web server settings
#define API_TOKEN "test"
#define ENABLE_API_TOKEN false
#define ENABLE_SECURE_CORS false
#define ENABLE_WEBHANDLER true

// Version information
#define SOFTWARE_VERSION "V1.0.7"

// Pin Definitions
#define BUTTON_PIN      0
#define LED_DI_PIN      40
#define LED_CI_PIN      39
#define TFT_CS_PIN      4
#define TFT_SDA_PIN     3
#define TFT_SCL_PIN     5
#define TFT_DC_PIN      2
#define TFT_RES_PIN     1
#define TFT_LEDA_PIN    38
#define SD_MMC_D0_PIN   14
#define SD_MMC_D1_PIN   17
#define SD_MMC_D2_PIN   21
#define SD_MMC_D3_PIN   18
#define SD_MMC_CLK_PIN  12
#define SD_MMC_CMD_PIN  16

#endif // GLOBALS_H
