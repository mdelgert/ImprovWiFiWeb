#pragma once

#include "Globals.h"
#include "ActionHandler.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

class ServeActions {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void handleGet(AsyncWebServer& server);
    static void handleSet(AsyncWebServer& server);
};