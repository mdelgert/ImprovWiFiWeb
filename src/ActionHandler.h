#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include "Globals.h"
#include <ArduinoJson.h>

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
        "action": "led_color",
        "parameters": {
            "color": "green",
            "brightness": 100
        }
    })";

    // Call ActionHandler with the JSON string
    ActionHandler::processMessage(jsonMessage);

    // Example JSON
    JsonDocument doc;
    doc["action"] = "tft_message";
    doc["parameters"]["message"] = "Hello, ESP32!";

    // Call ActionHandler with the JsonDocument
    ActionHandler::processMessage(doc);

*/

