#include "PreferencesHandler.h"

// Define static members
Preferences PreferencesHandler::preferences;
const char* PreferencesHandler::namespaceName = nullptr;
bool PreferencesHandler::initialized = false;

void PreferencesHandler::ensureInitialized() {
    if (!initialized) {
        preferences.begin(namespaceName, false);
        initialized = true;
        debugI("PreferencesHandler initialized with namespace: %s", namespaceName);
    }
}

void PreferencesHandler::init(const char* namespaceName) {
    PreferencesHandler::namespaceName = namespaceName;
    ensureInitialized();
}

void PreferencesHandler::clear() {
    ensureInitialized();
    preferences.clear();
    debugI("Preferences cleared for namespace: %s", namespaceName);
}

void PreferencesHandler::setValue(const String& key, const String& value) {
    ensureInitialized();
    preferences.putString(key.c_str(), value);
    //debugI("Set key: %s to value: %s", key.c_str(), value.c_str());
}

bool PreferencesHandler::getValue(const String& key, String& outValue) {
    ensureInitialized();
    outValue = preferences.getString(key.c_str(), "");
    //debugI("Retrieved key: %s with value: %s", key.c_str(), outValue.c_str());
    return !outValue.isEmpty();
}
