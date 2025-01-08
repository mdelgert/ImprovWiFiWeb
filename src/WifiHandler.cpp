#include "WifiHandler.h"

static String ssid, password;
static NonBlockingTimer myTimer(15000);
static DNSServer dnsServer;
static IPAddress apIP(192, 168, 4, 1);
static IPAddress netMsk(255, 255, 255, 0);

void WifiHandler::init()
{
    debugI("WifiHandler initialized");
    GfxHandler::printMessage("WifiHandler initialized");
    //WiFi.mode(WIFI_STA);
    //WiFi.mode(WIFI_AP);
    WiFi.mode(WIFI_AP_STA);
    connectToWifi();
    //startAccessPoint();
}

void WifiHandler::connectToWifi()
{
    // Must be WIFI_STA or WIFI_AP_STA mode
    PreferencesHandler::getValue("wifi_ssid", ssid, SECURE_WIFI_SSID);
    PreferencesHandler::getValue("wifi_password", password, SECURE_WIFI_PASSWORD);

    WiFi.begin(ssid.c_str(), password.c_str());
    
    while (WiFi.status() != WL_CONNECTED)
    {
        if (myTimer.isReady())
        {
            debugE("Failed to connect to WiFi. Starting Access Point...");
            GfxHandler::printMessage("Failed to connect to WiFi 1!");
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        String ipAddress = WiFi.localIP().toString();
        debugI("IP: %s", ipAddress.c_str());
        GfxHandler::printMessage("IP: " + ipAddress);
        Debug.begin(HOST_NAME);
        initializeMDNS();
    }
    else
    {
        debugE("Failed to connect to WiFi!");
        GfxHandler::printMessage("Failed to connect to WiFi 2!");
    }
}

void WifiHandler::startAccessPoint()
{
    // Must be WIFI_AP or WIFI_AP_STA mode

    if (WiFi.softAP(HOST_NAME))
    {
        WiFi.softAPConfig(apIP, apIP, netMsk);
        debugI("Access Point started. SSID: %s", HOST_NAME);
        GfxHandler::printMessage("Access Point started. SSID: " + String(HOST_NAME));
        debugI("AP IP: %s", apIP.toString().c_str());
        GfxHandler::printMessage("AP IP: " + apIP.toString());
    }
    else
    {
        debugE("Failed to start Access Point!");
        GfxHandler::printMessage("Failed to start AP!");
    }

    dnsServer.start(53, "*", WiFi.softAPIP());
    debugI("DNS Server started to route all traffic to AP IP");
}

void WifiHandler::initializeMDNS()
{
    if (!MDNS.begin(HOST_NAME))
    {
        debugE("Error setting up mDNS responder!");
    }
    else
    {
        debugI("mDNS responder started. Hostname: %s.local", HOST_NAME);
        MDNS.addService("http", "tcp", 80);
    }
}

void WifiHandler::loop()
{
    // if (WiFi.status() == WL_CONNECTED)
    // {
    //     dnsServer.processNextRequest();
    // }
    
    // if (WiFi.status() != WL_CONNECTED)
    // {
    //     if (myTimer.isReady())
    //     {
    //         debugW("Lost WiFi connection!");
    //         GfxHandler::printMessage("WiFi disconnected!");
    //     }
    // }
}