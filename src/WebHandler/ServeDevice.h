#pragma once

#ifdef ENABLE_WEB_HANDLER

#include "Globals.h"
#include "TimeHandler.h"
#include <WiFi.h>
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class ServeDevice {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleDeviceInfo(AsyncWebServer& server);
    static void handleDeviceReboot(AsyncWebServer& server);
    static void handleDeviceWifiNetworks(AsyncWebServer& server);
    static void handleDeviceBackup(AsyncWebServer& server);
};

#endif // ENABLE_WEB_HANDLER