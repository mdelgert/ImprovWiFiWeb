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
    settings.apiKey = preferences.getString("apiKey", settings.apiKey);
    settings.setupMode = preferences.getBool("setupMode", settings.setupMode);
    settings.defaulTimeout = preferences.getInt("defaulTimeout", settings.defaulTimeout);
    settings.apiToken = preferences.getBool("apiToken", settings.apiToken);
    settings.cors = preferences.getBool("cors", settings.cors);
    settings.WebHandler = preferences.getBool("webHandler", settings.WebHandler);
    settings.WifiScan = preferences.getBool("wifiScan", settings.WifiScan);
    settings.RemoteDebugger = preferences.getBool("remoteDebugger", settings.RemoteDebugger);

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
    preferences.putString("apiKey", settings.apiKey);
    preferences.putBool("setupMode", settings.setupMode);
    preferences.putInt("defaulTimeout", settings.defaulTimeout);
    preferences.putBool("apiToken", settings.apiToken);
    preferences.putBool("cors", settings.cors);
    preferences.putBool("webHandler", settings.WebHandler);
    preferences.putBool("wifiScan", settings.WifiScan);
    preferences.putBool("remoteDebugger", settings.RemoteDebugger);

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
