#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include "Globals.h"
#include <ESPAsyncWebServer.h>
#include "NonBlockingTimer.h"
#include "EmbeddedFiles.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include "PreferencesHandler.h"
#include "ServeDevice.h"
#include "ServeSettings.h"
#include "ServeActions.h"

class WebHandler
{
public:
    static void printRequestBody(AsyncWebServerRequest* request, uint8_t* data, size_t len);
    static void sendErrorResponse(AsyncWebServerRequest* request, int statusCode, const char* message, bool checkToken = true);
    static void sendSuccessResponse(AsyncWebServerRequest* request, const char* message, JsonDocument* data = nullptr, bool checkToken = true);
    static void init();
    static void loop();
    
private:
    static NonBlockingTimer myTimer;
    static AsyncWebServer server;
    static void serveRoot();
    static void serveEmbeddedFile(const char *path, const uint8_t *start, const uint8_t *end, const char *contentType);
    static bool isTokenValid(AsyncWebServerRequest* request);
    static void addCorsHeaders(AsyncWebServerResponse* response);
    static void serveNotFound();
};

#endif
