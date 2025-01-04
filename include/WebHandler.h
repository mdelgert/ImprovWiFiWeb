#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include <ESPAsyncWebServer.h>
#include "Globals.h"
#include "NonBlockingTimer.h"
#include "EmbeddedFiles.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

class WebHandler
{
private:
public:
    static NonBlockingTimer myTimer;
    static AsyncWebServer server;
    static void init();
    static void loop();
};

#endif
