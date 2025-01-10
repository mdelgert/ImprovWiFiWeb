#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include <ArduinoJson.h>
#include "Globals.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"
#include "LEDHandler.h"

class ActionHandler {

public:
    static void processMessage(const String& input);
    static void processMessage(const JsonDocument& doc);
private:
};

#endif

/* Example usage:

#include "ActionHandler.h"

    // Example JSON as a string
    String jsonMessage = R"({
        "action": "reboot"
    })";

    // Call ActionHandler with the JSON string
    ActionHandler::processMessage(jsonMessage);

    // Example JSON
    JsonDocument doc;
    doc["action"] = "tft";
    doc["message"] = "Hello!";

    // Call ActionHandler with the JsonDocument
    ActionHandler::processMessage(doc);

*/

