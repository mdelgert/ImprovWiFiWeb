#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include "Globals.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include "ConfigManager.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

class WifiHandler
{
private:
    static void connectToWifi();
    static void startAccessPoint();
    static void initializeMDNS();
    static void scanAndSaveNetworks(const char *filePath);
public:
    static void init();
    static void loop();
};

#endif
