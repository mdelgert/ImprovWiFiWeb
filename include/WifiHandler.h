#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include "Globals.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>
#include "PreferencesHandler.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"

class WifiHandler
{
private:
    static void connectToWifi();
    static void startAccessPoint();
    static void initializeMDNS();
public:
    static void init();
    static void loop();
};

#endif
