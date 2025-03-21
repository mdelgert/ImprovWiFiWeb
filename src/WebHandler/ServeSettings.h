#pragma once

#ifdef ENABLE_WEB_HANDLER

#include "Globals.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "NonBlockingTimer.h"

class ServeSettings {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleGetSettings(AsyncWebServerRequest *request);
    static void handleSetSettings(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    static void handleGetSettingsArchieve(AsyncWebServer& server);
    static void handleSetSettingsArchieve(AsyncWebServer& server);
};

#endif // ENABLE_WEB_HANDLER