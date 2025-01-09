#include "ServeTemplate.h"

void ServeTemplate::registerEndpoints(AsyncWebServer& server) {
    handleGetRequest(server);
    handleSetRequest(server);
}

void ServeTemplate::handleGetRequest(AsyncWebServer& server) {
    server.on("/template/get", HTTP_GET, [](AsyncWebServerRequest* request) {
        debugI("Received GET request on /template/get");

        // Create a JSON document for the response
        JsonDocument doc;
        doc["status"] = "success";
        doc["message"] = "GET response template";
        doc["data"] = "This is a JSON response";

        // Serialize JSON to a string
        String jsonResponse;
        serializeJson(doc, jsonResponse);

        // Send the response
        request->send(200, "application/json", jsonResponse);
    });
}

void ServeTemplate::handleSetRequest(AsyncWebServer& server) {
    server.on("/template/set", HTTP_POST, [](AsyncWebServerRequest* request) {}, 
        NULL, 
        [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
            debugI("Received POST request on /template/set");

            // Debugging: Print the request body
            printRequestBody(request, data, len);

            // Parse the JSON payload
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, data, len);

            if (error) {
                debugE("JSON deserialization failed: %s", error.c_str());
                request->send(400, "application/json", 
                    "{\"status\":\"error\",\"message\":\"Invalid JSON payload\"}");
                return;
            }

            // Extracting data for debugging purposes
            const char* exampleValue = doc["example"] | "undefined";
            debugI("Extracted JSON value: example=%s", exampleValue);

            // Respond with success
            JsonDocument responseDoc;
            responseDoc["status"] = "success";
            responseDoc["message"] = "Data received successfully";
            String jsonResponse;
            serializeJson(responseDoc, jsonResponse);

            request->send(200, "application/json", jsonResponse);
    });
}

void ServeTemplate::printRequestBody(AsyncWebServerRequest* request, uint8_t* data, size_t len) {
    String requestBody = "";
    for (size_t i = 0; i < len; i++) {
        requestBody += (char)data[i];
    }
    debugI("Request Body: %s", requestBody.c_str());
}
