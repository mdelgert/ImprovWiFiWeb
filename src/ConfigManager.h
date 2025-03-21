#pragma once

#include "Globals.h"
#include <Preferences.h>
#include <Arduino.h>
// Sub-struct for device info
struct DeviceSettings {
    String name = SECURE_DEVICE_NAME;
    bool setupMode = SETUP_MODE;
    String timezone;
    int defaultTimeout = DEFAULT_TIMEOUT;
    uint64_t bootCount = 0;
    uint64_t bootTime = 0;
    uint64_t upTime = 0;
};

// Sub-struct for Wi-Fi
struct WiFiSettings {
    String ssid = SECURE_WIFI_SSID;
    String password = SECURE_WIFI_PASSWORD;
    bool scan = true;
};

// Sub-struct for MQTT
struct MqttSettings {
    bool enabled = false;
    String server = SECURE_MQTT_SERVER;
    int port = SECURE_MQTT_PORT;
    bool ssl = SECURE_MQTT_SSL;
    String username = SECURE_MQTT_USERNAME;
    String password = SECURE_MQTT_PASSWORD;
    String subTopic = SECURE_MQTT_SUB_TOPIC;
    String pubTopic = SECURE_MQTT_PUB_TOPIC;
};

// Sub-struct for security/auth
struct SecuritySettings {
    String apiKey = SECURE_API_KEY;
    bool apiToken = API_TOKEN;
    String otaPassword = SECURE_OTA_PASSWORD;
};

// Sub-struct for feature toggles
struct FeatureSettings {
    bool cors = CORS;
    bool webHandler = WEBHANDLER;
};

// Main Settings container
struct Settings {
    DeviceSettings device;
    WiFiSettings wifi;
    MqttSettings mqtt;
    SecuritySettings security;
    FeatureSettings features;
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