#ifdef ENABLE_WEB_HANDLER

#include "ServeSettings.h"

static NonBlockingTimer delayTimer(500);

void ServeSettings::registerEndpoints(AsyncWebServer &server)
{
    handleGetSettings(server);
    handleSetSettings(server);
}

void ServeSettings::handleGetSettings(AsyncWebServer &server)
{
    server.on("/settings/get", HTTP_GET, [](AsyncWebServerRequest *request){
        
        debugV("Received GET request on /settings/get");

        JsonDocument doc;

        doc["device_name"] = settings.deviceName;
        doc["time_zone"] = settings.timezone;
        doc["wifi_ssid"] = settings.wifiSSID;
        doc["wifi_scan"] = settings.wifiScan;
        doc["wifi_password"] = settings.wifiPassword;
        doc["mqtt_enabled"] = settings.mqttEnabled;
        doc["mqtt_server"] = settings.mqttServer;
        doc["mqtt_port"] = settings.mqttPort;
        doc["mqtt_username"] = settings.mqttUsername;
        doc["mqtt_password"] = settings.mqttPassword;
        doc["mqtt_ssl"] = settings.mqttSsl;
        doc["mqtt_topic_sub"] = settings.mqttSubTopic;
        doc["mqtt_topic_pub"] = settings.mqttPubTopic;
        doc["api_key"] = settings.apiKey;

        WebHandler::sendSuccessResponse(request, "Settings retrieved successfully", &doc); });
}

void ServeSettings::handleSetSettings(AsyncWebServer &server)
{
    server.on("/settings/set", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        
        debugV("Received POST request on /settings/set");

        WebHandler::printRequestBody(request, data, len);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, data, len);

        if (error) {
            debugE("JSON deserialization failed: %s", error.c_str());
            WebHandler::sendErrorResponse(request, 400, "Invalid JSON payload");
            return;
        }

        settings.deviceName = doc["device_name"] | settings.deviceName;
        settings.timezone = doc["time_zone"] | settings.timezone;
        settings.wifiSSID = doc["wifi_ssid"] | settings.wifiSSID;
        settings.wifiScan = doc["wifi_scan"] | settings.wifiScan;
        settings.wifiPassword = doc["wifi_password"] | settings.wifiPassword;
        settings.mqttEnabled = doc["mqtt_enabled"] | settings.mqttEnabled;
        settings.mqttServer = doc["mqtt_server"] | settings.mqttServer;
        settings.mqttPort = doc["mqtt_port"] | settings.mqttPort;
        settings.mqttUsername = doc["mqtt_username"] | settings.mqttUsername;
        settings.mqttPassword = doc["mqtt_password"] | settings.mqttPassword;
        settings.mqttSsl = doc["mqtt_ssl"] | settings.mqttSsl;
        settings.mqttSubTopic = doc["mqtt_topic_sub"] | settings.mqttSubTopic;
        settings.mqttPubTopic = doc["mqtt_topic_pub"] | settings.mqttPubTopic;
        settings.apiKey = doc["api_key"] | settings.apiKey;

        // Save updated settings
        ConfigManager::save();

        // Send success response
        WebHandler::sendSuccessResponse(request, "Settings updated successfully");

        // if (delayTimer.isReady())
        // {
        //     ESP.restart();
        // }
    });
}

#endif // ENABLE_WEB_HANDLER