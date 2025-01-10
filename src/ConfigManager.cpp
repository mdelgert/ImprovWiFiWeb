#include "ConfigManager.h"

// Global settings object
Settings settings;

// Preferences instance
Preferences ConfigManager::preferences;

// Initialize preferences and load settings
void ConfigManager::init() {
    preferences.begin("config", false);
    load();
}

// Load settings with defaults
void ConfigManager::load() {
    settings.wifiSSID = preferences.getString("wifiSSID", settings.wifiSSID);
    settings.wifiPassword = preferences.getString("wifiPassword", settings.wifiPassword);
    settings.deviceName = preferences.getString("deviceName", settings.deviceName);
    settings.setupMode = preferences.getBool("setupMode", settings.setupMode);
    settings.timeout = preferences.getInt("timeout", settings.timeout);
    settings.ledEnabled = preferences.getBool("ledEnabled", settings.ledEnabled);
}

// Save settings to preferences
void ConfigManager::save() {
    preferences.putString("wifiSSID", settings.wifiSSID);
    preferences.putString("wifiPassword", settings.wifiPassword);
    preferences.putString("deviceName", settings.deviceName);
    preferences.putBool("setupMode", settings.setupMode);
    preferences.putInt("timeout", settings.timeout);
    preferences.putBool("ledEnabled", settings.ledEnabled);
}

// Clear all preferences
void ConfigManager::clear() {
    preferences.clear();
}
