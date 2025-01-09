#include "ServeActions.h"

void ServeActions::registerEndpoints(AsyncWebServer &server)
{
    handleGet(server);
    handleSet(server);
}

void ServeActions::handleGet(AsyncWebServer &server)
{
    server.on("/actions/get", HTTP_GET, [](AsyncWebServerRequest *request){
        debugI("Received GET request on /actions/get");

        File file = LittleFS.open("/actions.json", "r");
        if (!file) {
            debugE("Failed to open /actions.json");
            WebHandler::sendErrorResponse(request, 400, "File not found");
            return;
        }

        String json = file.readString();
        file.close();
        debugI("Serving /actions.json");

        JsonDocument doc; // Use the simplified declaration
        DeserializationError error = deserializeJson(doc, json);

        if (error) {
            debugE("Failed to parse saved JSON: %s", error.c_str());
             WebHandler::sendErrorResponse(request, 500, "Internal server error");
            return;
        }

        WebHandler::sendSuccessResponse(request, "GET response template", &doc); });
}

void ServeActions::handleSet(AsyncWebServer &server)
{
    server.on("/actions/set", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
            debugI("Received POST request on /actions/set");

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

            // Convert JSON to a string
            String jsonString;
            serializeJson(doc, jsonString);

            // Save JSON to LittleFS
            File file = LittleFS.open("/actions.json", "w");
            if (!file) {
                debugE("Failed to open file for writing");
                WebHandler::sendErrorResponse(request, 500, "Failed to save file");
                return;
            }
            file.print(jsonString);
            file.close();

            debugI("JSON saved to /actions.json");

            // Respond with success
            WebHandler::sendSuccessResponse(request, "Data received successfully"); });
}
