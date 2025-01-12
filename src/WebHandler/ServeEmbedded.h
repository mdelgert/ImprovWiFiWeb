#pragma once

#include "Globals.h"
#include "ServeEmbeddedFiles.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

class ServeEmbedded {
public:
    static void registerEndpoints(AsyncWebServer& server);

private:
    static void serveEmbeddedFile(AsyncWebServer &server, const char *path, const uint8_t *start, const uint8_t *end, const char *contentType);
    static void handleGetRequest(AsyncWebServer& server);
};