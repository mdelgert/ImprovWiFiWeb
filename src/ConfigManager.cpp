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

    settings.deviceName = preferences.getString("deviceName", settings.deviceName);
    settings.wifiSSID = preferences.getString("wifiSSID", settings.wifiSSID);
    settings.wifiPassword = preferences.getString("wifiPassword", settings.wifiPassword);
    settings.mqttServer = preferences.getString("mqttServer", settings.mqttServer);
    settings.mqttPort = preferences.getInt("mqttPort", settings.mqttPort);
    settings.mqttUsername = preferences.getString("mqttUsername", settings.mqttUsername);
    settings.mqttPassword = preferences.getString("mqttPassword", settings.mqttPassword);
    settings.mqttSsl = preferences.getBool("mqttSsl", settings.mqttSsl);
    settings.mqttSubTopic = preferences.getString("mqttSubTopic", settings.mqttSubTopic);
    settings.mqttPubTopic = preferences.getString("mqttPubTopic", settings.mqttPubTopic);
    settings.apiKey = preferences.getString("apiKey", settings.apiKey);
    settings.otaPassword = preferences.getString("otaPassword", settings.otaPassword);
    settings.setupMode = preferences.getBool("setupMode", settings.setupMode);
    settings.defaulTimeout = preferences.getInt("defaulTimeout", settings.defaulTimeout);
    settings.apiToken = preferences.getBool("apiToken", settings.apiToken);
    settings.cors = preferences.getBool("cors", settings.cors);
    settings.webHandler = preferences.getBool("webHandler", settings.webHandler);
    settings.wifiScan = preferences.getBool("wifiScan", settings.wifiScan);
    settings.mqttEnabled = preferences.getBool("mqttEnabled", settings.mqttEnabled);
    settings.timezone = preferences.getString("timezone", settings.timezone);
    settings.bootCount = preferences.getUInt("bootCount", settings.bootCount);
    settings.bootTime = preferences.getULong("bootTime", settings.bootTime);
    
    preferences.end();

    debugI("ConfigManager load() namespace: %s", ns);
}

// Save settings to preferences
void ConfigManager::save() {
    if (!preferences.begin(ns, false)) {
        debugE("Failed to open preferences for saving.");
        return;
    }

    preferences.putString("deviceName", settings.deviceName);
    preferences.putString("wifiSSID", settings.wifiSSID);
    preferences.putString("wifiPassword", settings.wifiPassword);
    preferences.putString("mqttServer", settings.mqttServer);
    preferences.putInt("mqttPort", settings.mqttPort);
    preferences.putString("mqttUsername", settings.mqttUsername);
    preferences.putString("mqttPassword", settings.mqttPassword);
    preferences.putBool("mqttSsl", settings.mqttSsl);
    preferences.putString("mqttSubTopic", settings.mqttSubTopic);
    preferences.putString("mqttPubTopic", settings.mqttPubTopic);
    preferences.putString("apiKey", settings.apiKey);
    preferences.putString("otaPassword", settings.otaPassword);
    preferences.putBool("setupMode", settings.setupMode);
    preferences.putInt("defaulTimeout", settings.defaulTimeout);
    preferences.putBool("apiToken", settings.apiToken);
    preferences.putBool("cors", settings.cors);
    preferences.putBool("webHandler", settings.webHandler);
    preferences.putBool("wifiScan", settings.wifiScan);
    preferences.putBool("mqttEnabled", settings.mqttEnabled);
    preferences.putString("timezone", settings.timezone);
    preferences.putUInt("bootCount", settings.bootCount);
    preferences.putULong("bootTime", settings.bootTime);
    
    preferences.end();

    debugI("ConfigManager save() namespace: %s", ns);
}

// Clear all preferences
void ConfigManager::clear() {
    if (!preferences.begin(ns, false)) {
        debugE("Failed to open preferences for clearing.");
        return;
    }

    preferences.clear();
    preferences.end();

    // Reset settings to defaults
    settings = Settings();

    debugI("ConfigManager clear() namespace: %s", ns);
}
