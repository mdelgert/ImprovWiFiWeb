#ifndef IMPROV_HANDLER_H
#define IMPROV_HANDLER_H

#include "Globals.h"
#include "ImprovWiFiLibrary.h"
#include "PreferencesHandler.h"
#include "GfxHandler.h"

class ImprovHandler
{
public:
    static void init();
    static void loop();

private:
    static ImprovWiFi improvSerial;
    static void onImprovWiFiErrorCb(ImprovTypes::Error err);
    static void onImprovWiFiConnectedCb(const char *ssid, const char *password);
};

#endif