#ifndef SERVE_BUTTONS_H
#define SERVE_BUTTONS_H

#include "Globals.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

class ServeButtons
{
public:
    static void registerEndpoints(AsyncWebServer &server);

private:
    static const char *BUTTONS_FILE; // JSON file path for buttons
    static void handleGetButtons(AsyncWebServerRequest *request);
    static void handleDeleteButton(AsyncWebServerRequest *request);
    static void handlePostButtons(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
};

#endif // SERVE_BUTTONS_H
