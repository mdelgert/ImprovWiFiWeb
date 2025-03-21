#include "ConfigManager.h"

// Global settings object
Settings settings;

// Preferences instance
Preferences ConfigManager::preferences;

// Namespace for preferences
const char *ns = "config";

// Initialize preferences and load settings
void ConfigManager::init() {
    load();
}

// Load settings with defaults
void ConfigManager::load() {
    if (!preferences.begin(ns, false)) {
        debugE("Failed to open preferences for loading.");
        return;
    }

    // Device
    settings.device.name         = preferences.getString("deviceName", settings.device.name);
    settings.device.timezone     = preferences.getString("timezone", settings.device.timezone);
    settings.device.setupMode    = preferences.getBool("setupMode", settings.device.setupMode);
    settings.device.defaultTimeout = preferences.getInt("defaultTimeout", settings.device.defaultTimeout);
    settings.device.bootCount    = preferences.getULong("bootCount", settings.device.bootCount);
    settings.device.bootTime     = preferences.getULong("bootTime", settings.device.bootTime);

    // WiFi
    settings.wifi.ssid           = preferences.getString("wifiSSID", settings.wifi.ssid);
    settings.wifi.password       = preferences.getString("wifiPassword", settings.wifi.password);
    settings.wifi.scan           = preferences.getBool("wifiScan", settings.wifi.scan);

    // MQTT
    settings.mqtt.enabled        = preferences.getBool("mqttEnabled", settings.mqtt.enabled);
    settings.mqtt.server         = preferences.getString("mqttServer", settings.mqtt.server);
    settings.mqtt.port           = preferences.getInt("mqttPort", settings.mqtt.port);
    settings.mqtt.ssl            = preferences.getBool("mqttSsl", settings.mqtt.ssl);
    settings.mqtt.username       = preferences.getString("mqttUsername", settings.mqtt.username);
    settings.mqtt.password       = preferences.getString("mqttPassword", settings.mqtt.password);
    settings.mqtt.subTopic       = preferences.getString("mqttSubTopic", settings.mqtt.subTopic);
    settings.mqtt.pubTopic       = preferences.getString("mqttPubTopic", settings.mqtt.pubTopic);

    // Security
    settings.security.apiKey     = preferences.getString("apiKey", settings.security.apiKey);
    settings.security.apiToken   = preferences.getBool("apiToken", settings.security.apiToken);
    settings.security.otaPassword = preferences.getString("otaPassword", settings.security.otaPassword);

    // Features
    settings.features.cors       = preferences.getBool("cors", settings.features.cors);
    settings.features.webHandler = preferences.getBool("webHandler", settings.features.webHandler);

    preferences.end();
    debugI("ConfigManager loaded settings from namespace: %s", ns);
}

// Save settings to preferences
void ConfigManager::save() {
    if (!preferences.begin(ns, false)) {
        debugE("Failed to open preferences for saving.");
        return;
    }

    // Device
    preferences.putString("deviceName", settings.device.name);
    preferences.putString("timezone", settings.device.timezone);
    preferences.putBool("setupMode", settings.device.setupMode);
    preferences.putInt("defaultTimeout", settings.device.defaultTimeout);
    preferences.putULong("bootCount", settings.device.bootCount);
    preferences.putULong("bootTime", settings.device.bootTime);

    // WiFi
    preferences.putString("wifiSSID", settings.wifi.ssid);
    preferences.putString("wifiPassword", settings.wifi.password);
    preferences.putBool("wifiScan", settings.wifi.scan);

    // MQTT
    preferences.putBool("mqttEnabled", settings.mqtt.enabled);
    preferences.putString("mqttServer", settings.mqtt.server);
    preferences.putInt("mqttPort", settings.mqtt.port);
    preferences.putBool("mqttSsl", settings.mqtt.ssl);
    preferences.putString("mqttUsername", settings.mqtt.username);
    preferences.putString("mqttPassword", settings.mqtt.password);
    preferences.putString("mqttSubTopic", settings.mqtt.subTopic);
    preferences.putString("mqttPubTopic", settings.mqtt.pubTopic);

    // Security
    preferences.putString("apiKey", settings.security.apiKey);
    preferences.putBool("apiToken", settings.security.apiToken);
    preferences.putString("otaPassword", settings.security.otaPassword);

    // Features
    preferences.putBool("cors", settings.features.cors);
    preferences.putBool("webHandler", settings.features.webHandler);

    preferences.end();
    debugI("ConfigManager saved settings to namespace: %s", ns);
}

// Clear all preferences
void ConfigManager::clear() {
    if (!preferences.begin(ns, false)) {
        debugE("Failed to open preferences for clearing.");
        return;
    }

    preferences.clear();
    preferences.end();

    settings = Settings(); // reset to defaults
    debugI("ConfigManager cleared preferences in namespace: %s", ns);
}
