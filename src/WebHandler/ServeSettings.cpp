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

        // Device
        doc["device_name"]       = settings.device.name;
        doc["time_zone"]         = settings.device.timezone;
        doc["setup_mode"]        = settings.device.setupMode;
        doc["default_timeout"]   = settings.device.defaultTimeout;
        doc["boot_count"]        = settings.device.bootCount;
        doc["boot_time"]         = settings.device.bootTime;

        // WiFi
        doc["wifi_ssid"]         = settings.wifi.ssid;
        doc["wifi_password"]     = settings.wifi.password;
        doc["wifi_scan"]         = settings.wifi.scan;

        // MQTT
        doc["mqtt_enabled"]      = settings.mqtt.enabled;
        doc["mqtt_server"]       = settings.mqtt.server;
        doc["mqtt_port"]         = settings.mqtt.port;
        doc["mqtt_username"]     = settings.mqtt.username;
        doc["mqtt_password"]     = settings.mqtt.password;
        doc["mqtt_ssl"]          = settings.mqtt.ssl;
        doc["mqtt_topic_sub"]    = settings.mqtt.subTopic;
        doc["mqtt_topic_pub"]    = settings.mqtt.pubTopic;

        // Security
        doc["api_key"]           = settings.security.apiKey;
        doc["api_token"]         = settings.security.apiToken;
        doc["ota_password"]      = settings.security.otaPassword;

        // Features
        doc["cors"]              = settings.features.cors;
        doc["web_handler"]       = settings.features.webHandler;

        WebHandler::sendSuccessResponse(request, "Settings retrieved successfully", &doc);
    });
}

void ServeSettings::handleSetSettings(AsyncWebServer &server)
{
    server.on("/settings/set", HTTP_POST, [](AsyncWebServerRequest *request) {}, nullptr,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
            debugV("Received POST request on /settings/set");

            WebHandler::printRequestBody(request, data, len);

            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, data, len);

            if (error) {
                debugE("JSON deserialization failed: %s", error.c_str());
                WebHandler::sendErrorResponse(request, 400, "Invalid JSON payload");
                return;
            }

            // Device
            settings.device.name         = doc["device_name"] | settings.device.name;
            settings.device.timezone     = doc["time_zone"] | settings.device.timezone;
            settings.device.setupMode    = doc["setup_mode"] | settings.device.setupMode;
            settings.device.defaultTimeout = doc["default_timeout"] | settings.device.defaultTimeout;
            settings.device.bootCount    = doc["boot_count"] | settings.device.bootCount;
            settings.device.bootTime     = doc["boot_time"] | settings.device.bootTime;

            // WiFi
            settings.wifi.ssid           = doc["wifi_ssid"] | settings.wifi.ssid;
            settings.wifi.password       = doc["wifi_password"] | settings.wifi.password;
            settings.wifi.scan           = doc["wifi_scan"] | settings.wifi.scan;

            // MQTT
            settings.mqtt.enabled        = doc["mqtt_enabled"] | settings.mqtt.enabled;
            settings.mqtt.server         = doc["mqtt_server"] | settings.mqtt.server;
            settings.mqtt.port           = doc["mqtt_port"] | settings.mqtt.port;
            settings.mqtt.ssl            = doc["mqtt_ssl"] | settings.mqtt.ssl;
            settings.mqtt.username       = doc["mqtt_username"] | settings.mqtt.username;
            settings.mqtt.password       = doc["mqtt_password"] | settings.mqtt.password;
            settings.mqtt.subTopic       = doc["mqtt_topic_sub"] | settings.mqtt.subTopic;
            settings.mqtt.pubTopic       = doc["mqtt_topic_pub"] | settings.mqtt.pubTopic;

            // Security
            settings.security.apiKey     = doc["api_key"] | settings.security.apiKey;
            settings.security.apiToken   = doc["api_token"] | settings.security.apiToken;
            settings.security.otaPassword = doc["ota_password"] | settings.security.otaPassword;

            // Features
            settings.features.cors       = doc["cors"] | settings.features.cors;
            settings.features.webHandler = doc["web_handler"] | settings.features.webHandler;

            // Save updated settings
            ConfigManager::save();

            WebHandler::sendSuccessResponse(request, "Settings updated successfully");

            // Optional reboot if needed
            // if (delayTimer.isReady()) {
            //     ESP.restart();
            // }
        }
    );
}

#endif // ENABLE_WEB_HANDLER
