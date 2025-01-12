#pragma once

#include "Globals.h"
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
};
