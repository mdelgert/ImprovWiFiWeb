#pragma once

#define WIFI_NETWORKS_FILE "/data/wifi_networks.json"
#define BUTTONS_FILE "/data/buttons.json"
#define TIMEZONES_FILE "/data/timezones.json"

// Custom USB descriptors
#define CUSTOM_PRODUCT_NAME "USB KeyboardMouse"
#define CUSTOM_MANUFACTURER "Demo"
#define CUSTOM_SERIAL_NUMBER "123456789"

//#include "Secure.h"
#include "SecureExample.h"
#include "ConfigManager.h"
#include "NonBlockingTimer.h"
#include "RemoteDebugHandler.h"
#include "BoardPins.h"
#include "CommandHandler.h"