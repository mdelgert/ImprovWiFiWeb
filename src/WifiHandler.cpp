#include "WifiHandler.h"
#include "Secure.h"

NonBlockingTimer WifiHandler::myTimer(1000);

void WifiHandler::init()
{
    debugI("WifiHandler initialized");
    GfxHandler::printMessage("WifiHandler initialized");

    String ssid = SECURE_WIFI_SSID; // Default to Secure.h values
    String password = SECURE_WIFI_PASSWORD;

    // Attempt to retrieve WiFi credentials from Preferences
    bool hasSsid = PreferencesHandler::getValue("wifi_ssid", ssid);
    bool hasPassword = PreferencesHandler::getValue("wifi_password", password);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    if (hasSsid && hasPassword)
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            if (myTimer.isReady())
            {
                debugI("Connecting to WiFi...");
                GfxHandler::printMessage("Connecting to WiFi...");
            }
        }
    }
    else
    {
        debugE("No valid WiFi credentials! Using defaults.");
        GfxHandler::printMessage("No valid WiFi credentials!");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        String ipAddress = WiFi.localIP().toString();
        debugI("IP: %s", ipAddress.c_str());
        GfxHandler::printMessage("IP: " + ipAddress);
        Debug.begin(HOST_NAME);
    }
    else
    {
        debugE("Failed to connect to WiFi!");
        GfxHandler::printMessage("Failed to connect to WiFi!");
    }
}

void WifiHandler::loop()
{
    // debugD("WifiHandler loop");
}
