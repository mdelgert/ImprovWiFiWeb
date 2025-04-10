#pragma once

#ifdef ENABLE_IMPROV_HANDLER

#include "Globals.h"
#include "ImprovWiFiLibrary.h"

class ImprovHandler
{
public:
    static void init();
    static void loop();

private:
    static ImprovWiFi improvSerial;
    static void onImprovWiFiErrorCb(ImprovTypes::Error err);
    static void onImprovWiFiConnectedCb(const char *ssid, const char *password);
    static void alternativeSetupMethod();
    static void scanAndSaveNetworks(const char *filePath);
};

#else // If ENABLE_IMPROV_HANDLER is NOT defined, use a no-op class

class ImprovHandler
{
public:
    static void init() {} // No-op
    static void loop() {} // No-op
};

#endif // ENABLE_IMPROV_HANDLER