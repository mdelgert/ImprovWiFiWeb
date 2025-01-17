#pragma once

#ifdef ENABLE_WEB_HANDLER

#include "Globals.h"
#include "WebHandler.h"
#include <ESPAsyncWebServer.h>

class ServeCommand
{
public:
    // Registers the endpoint for handling commands
    static void registerEndpoints(AsyncWebServer &server);

private:
    // Handles the POST request for executing commands
    static void handleCommandRequest(AsyncWebServer &server);
};

#endif // ENABLE_WEB_HANDLER
