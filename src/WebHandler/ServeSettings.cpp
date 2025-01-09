#include "ServeSettings.h"

static String ssid, password;

void ServeSettings::registerEndpoints(AsyncWebServer &server)
{
    handleGetSettings(server);
    handleSetSettings(server);
}

void ServeSettings::handleGetSettings(AsyncWebServer &server)
{
    server.on("/settings/get", HTTP_GET, [](AsyncWebServerRequest *request){
        debugI("Received GET request on /settings/get");

        PreferencesHandler::getValue("wifi_ssid", ssid, SECURE_WIFI_SSID);
        PreferencesHandler::getValue("wifi_password", password, SECURE_WIFI_PASSWORD);

        JsonDocument data;
        data["wifi_ssid"]   = ssid;
        data["wifi_password"] = password;

        WebHandler::sendSuccessResponse(request, "GET response template", &data); });
}

void ServeSettings::handleSetSettings(AsyncWebServer &server)
{
    server.on("/settings/set", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, 
                                          [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
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

            // Extract Wi-Fi credentials
            const char *ssid = doc["wifi_ssid"] | "";
            const char *password = doc["wifi_password"] | "";

            if (strlen(ssid) == 0 || strlen(password) == 0) {
                debugE("Wi-Fi credentials missing");
                WebHandler::sendErrorResponse(request, 400, "Missing Wi-Fi credentials");
                return;
            }

            // Save credentials to preferences
            PreferencesHandler::setValue("wifi_ssid", String(ssid));
            PreferencesHandler::setValue("wifi_password", String(password));

            // Respond with success
            WebHandler::sendSuccessResponse(request, "POST handleSetSettings saved successfully"); 
            });
}
