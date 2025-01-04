#include "ImprovHandler.h"

ImprovWiFi ImprovHandler::improvSerial(&Serial);

void ImprovHandler::init()
{
    improvSerial.setDeviceInfo(ImprovTypes::
                                   ChipFamily::CF_ESP32_S3,
                               "ImprovWiFi", SOFTWARE_VERSION,
                               "Demo", "http://{LOCAL_IPV4}");

    improvSerial.onImprovError(onImprovWiFiErrorCb);
    improvSerial.onImprovConnected(onImprovWiFiConnectedCb);
    debugD("ImprovWiFi initialized");
}

void ImprovHandler::loop()
{
    improvSerial.handleSerial();
}

void ImprovHandler::onImprovWiFiErrorCb(ImprovTypes::Error err)
{
    debugE("ImprovWiFi error occurred: %d", err);
}

void ImprovHandler::onImprovWiFiConnectedCb(const char *ssid, const char *password)
{
    PreferencesHandler::setValue("wifi_ssid", String(ssid));
    PreferencesHandler::setValue("wifi_password", String(password));
    debugD("WiFi credentials saved to preferences. SSID: %s", ssid);
    GfxHandler::printMessage("Rebooting...");
    debugI("Rebooting...");
    delay(1000);
    ESP.restart();
}