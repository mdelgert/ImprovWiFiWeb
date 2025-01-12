#pragma once

#include "Globals.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "NonBlockingTimer.h"

class ServeSettings {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleGetSettings(AsyncWebServer& server);
    static void handleSetSettings(AsyncWebServer& server);
};