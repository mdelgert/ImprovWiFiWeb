#include "ServeSettings.h"

void ServeSettings::registerEndpoints(AsyncWebServer &server)
{
    handleGetRequest(server);
    handleSetRequest(server);
}

void ServeSettings::handleGetRequest(AsyncWebServer &server)
{
    server.on("/settings/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        debugI("Received GET request on /settings/get");

        // Create a JSON response
        JsonDocument data;
        data["data"] = "This is a JSON response";

        WebHandler::sendSuccessResponse(request, "GET response template", &data); });
}

void ServeSettings::handleSetRequest(AsyncWebServer &server)
{
    server.on("/settings/set", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
            debugI("Received POST request on /settings/set");

            // Print the request body
            WebHandler::printRequestBody(request, data, len);

            // Parse JSON
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, data, len);

            if (error) {
                debugE("JSON deserialization failed: %s", error.c_str());
                WebHandler::sendErrorResponse(request, 400, "Invalid JSON payload");
                return;
            }

            // Extract a field for debugging
            const char* exampleValue = doc["example"] | "undefined";
            debugI("Extracted JSON value: example=%s", exampleValue);

            // Respond with success
            WebHandler::sendSuccessResponse(request, "Data received successfully"); });
}
