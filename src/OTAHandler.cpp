#ifdef ENABLE_OTA_HANDLER

#include "OTAHandler.h"

void OTAHandler::setupOTA()
{
    ArduinoOTA.onStart([]() {
        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
        debugI("OTA Start: Updating %s", type.c_str());
    });

    ArduinoOTA.onEnd([]() {
        debugI("OTA End");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        debugI("OTA Progress: %u%%", (progress * 100) / total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        debugE("OTA Error[%u]: %s", error, 
               error == OTA_AUTH_ERROR ? "Auth Failed" :
               error == OTA_BEGIN_ERROR ? "Begin Failed" :
               error == OTA_CONNECT_ERROR ? "Connect Failed" :
               error == OTA_RECEIVE_ERROR ? "Receive Failed" :
               "End Failed");
    });

    ArduinoOTA.begin();
    debugI("OTA setup complete");
}

void OTAHandler::init()
{
    debugI("Initializing OTAHandler");
    setupOTA();
}

void OTAHandler::loop()
{
    ArduinoOTA.handle();
}

void OTAHandler::triggerUpdate()
{
    debugI("Triggering OTA update manually");
    // Add logic for manual OTA trigger if needed
    // For example, call ArduinoOTA.handle() directly or start a custom OTA process
}

#endif // ENABLE_OTA_HANDLER
