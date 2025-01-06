#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include "Globals.h"
#include "Secure.h"
#include "PreferencesHandler.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"

class WifiHandler
{
private:

public:
    static NonBlockingTimer myTimer;
    static void init();
    static void loop();
};

#endif
