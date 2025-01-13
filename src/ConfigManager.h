#pragma once

#include "Globals.h"
#include <Preferences.h>
#include <Arduino.h>

// Struct for all settings
struct Settings {
    String deviceName = SECURE_DEVICE_NAME;
    String wifiSSID = SECURE_WIFI_SSID;
    String wifiPassword = SECURE_WIFI_PASSWORD;
    String mqttServer = SECURE_MQTT_SERVER;
    int mqttPort = SECURE_MQTT_PORT;
    String mqttUsername = SECURE_MQTT_USERNAME;
    String mqttPassword = SECURE_MQTT_PASSWORD;
    String mqttSubTopic = SECURE_MQTT_SUB_TOPIC;
    String mqttPubTopic = SECURE_MQTT_PUB_TOPIC;
    String apiKey = SECURE_API_KEY;
    String otaPassword = SECURE_OTA_PASSWORD;
    bool setupMode = SETUP_MODE;
    int defaulTimeout = DEFAULT_TIMEOUT;
    bool apiToken = API_TOKEN;
    bool cors = CORS;
    bool WebHandler = WEBHANDLER;
    bool WifiScan = WIFI_SCAN;
    String timezone = DEFAULT_TIMEZONE;
    uint64_t bootCount = 0;
    uint64_t bootTime = 0;
    // Settings not saved in preferences
    uint64_t upTime = 0;
    String currentTime = "";
    String currentDate = "";
};

// Global settings object
extern Settings settings;

// ConfigManager class declaration
class ConfigManager {
public:
    static void init();
    static void save();
    static void clear();

private:
    static void load();
    static Preferences preferences;
};