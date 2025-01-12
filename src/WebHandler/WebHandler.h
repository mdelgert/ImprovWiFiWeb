#pragma once

#include "Globals.h"
#include <ESPAsyncWebServer.h>
#include "ServeDevice.h"
#include "ServeSettings.h"
#include "ServeActions.h"
#include "ServeEmbedded.h"

class WebHandler
{
public:
    static void printRequestBody(AsyncWebServerRequest* request, uint8_t* data, size_t len);
    static void sendErrorResponse(AsyncWebServerRequest* request, int statusCode, const char* message, bool checkToken = true);
    static void sendSuccessResponse(AsyncWebServerRequest* request, const char* message, JsonDocument* data = nullptr, bool checkToken = true);
    static bool isTokenValid(AsyncWebServerRequest* request);
    static void addCorsHeaders(AsyncWebServerResponse* response);
    static void init();
    static void loop();
    
private:
    static NonBlockingTimer myTimer;
    static AsyncWebServer server;
    static void serveNotFound();
};