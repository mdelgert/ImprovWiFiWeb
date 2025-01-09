#ifndef SERVE_DEVICE_H
#define SERVE_DEVICE_H

#include "Globals.h"
#include <WiFi.h>
#include "WebHandler.h"
#include "NonBlockingTimer.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class ServeDevice {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleDeviceWifiNetworks(AsyncWebServer& server);
    static void handleDeviceInfo(AsyncWebServer& server);
    static void handleDeviceReboot(AsyncWebServer& server);
};

#endif
