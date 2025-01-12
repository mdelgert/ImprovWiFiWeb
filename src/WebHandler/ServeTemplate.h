#pragma once

#ifdef ENABLE_WEB_HANDLER

#include "Globals.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class ServeTemplate {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleGetRequest(AsyncWebServer& server);
    static void handleSetRequest(AsyncWebServer& server);
};

#endif // ENABLE_WEB_HANDLER