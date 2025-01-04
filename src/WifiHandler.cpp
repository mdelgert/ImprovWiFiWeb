#include "WifiHandler.h"

NonBlockingTimer WifiHandler::myTimer(5000);

void WifiHandler::init()
{
    debugI("WifiHandler initialized");
    GfxHandler::printMessage("WifiHandler initialized");

    String ssid, password;
    WiFi.mode(WIFI_STA);

    if (PreferencesHandler::getValue("wifi_ssid", ssid) && PreferencesHandler::getValue("wifi_password", password))
    {
        WiFi.begin(ssid.c_str(), password.c_str());
        while (WiFi.status() != WL_CONNECTED)
        {
            if (myTimer.isReady())
            {
                debugE("Failed WiFi!");
                GfxHandler::printMessage("Failed WiFi!");
                break;
            }
        }
    }
    else
    {
        debugE("No wifi credentials!");
        GfxHandler::printMessage("No wifi credentials!");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        debugI("IP: %s", WiFi.localIP().toString().c_str());
        GfxHandler::printMessage("IP: " + WiFi.localIP().toString());
        Debug.begin(HOST_NAME);
    }
    else
    {
        debugE("No WiFi!");
        GfxHandler::printMessage("No WiFi!");
    }
}

void WifiHandler::loop()
{
    // debugD("WifiHandler loop");
}
