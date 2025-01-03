#ifndef GLOBALS_H
#define GLOBALS_H

#include <RemoteDebug.h>

// Remote debug instance
#define HOST_NAME "remotedebug"
extern RemoteDebug Debug;

// Version information
#define SOFTWARE_VERSION "V1.0.4"

// Feature Flags
#define ENABLE_TFT true
#define ENABLE_SERIAL true
#define ENABLE_WIFI true
#define ENABLE_MQTT true
#define ENABLE_MQTT_LOGGER true
#define ENABLE_BLUETOOTH_SERVER true
#define ENABLE_WEBSOCKET true
#define ENABLE_WEBSOCKET_CERT true

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
