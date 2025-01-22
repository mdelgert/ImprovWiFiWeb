#ifdef ENABLE_WEB_HANDLER

#include "ServeDevice.h"

static NonBlockingTimer delayTimer(1000);

void ServeDevice::registerEndpoints(AsyncWebServer &server)
{
    handleDeviceInfo(server);
    handleDeviceReboot(server);
    handleDeviceWifiNetworks(server);
}

void ServeDevice::handleDeviceInfo(AsyncWebServer &server)
{
    server.on("/device/info", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        
        debugV("Serving /device/get");

        JsonDocument doc;

        doc["deviceName"]   = settings.deviceName;
        doc["timezone"]    = settings.timezone;
        
        //Need to cleanup when clock was not set caused reboot loop
        //doc["bootCount"]    = settings.bootCount;
        //doc["bootTime"] = settings.bootTime;
        //doc["upTime"]    = settings.upTime;
        //doc["currentTime"]  = TimeHandler::formatDateTime("%I:%M:%S %p");
        //doc["currentDate"]  = TimeHandler::formatDateTime("%m-%d-%Y");

        doc["ssid"]        = WiFi.SSID();
        doc["ip"]          = WiFi.localIP().toString();
        doc["mac"]         = WiFi.macAddress();
        doc["rssi"]        = WiFi.RSSI();
        doc["wifiMode"]    = WiFi.getMode();
        doc["wifiChannel"] = WiFi.channel();
        doc["tickRateHz"] = configTICK_RATE_HZ;
        doc["chipModel"]   = ESP.getChipModel();
        doc["chipRevision"] = (int)ESP.getChipRevision();
        doc["chipId"]      = ESP.getEfuseMac();
        doc["chipCores"] = ESP.getChipCores();
        doc["heapSize"]    = ESP.getHeapSize();
        doc["freeHeap"]    = ESP.getFreeHeap();
        doc["flashSize"]   = ESP.getFlashChipSize();
        doc["flashSpeed"]  = ESP.getFlashChipSpeed();
        doc["flashMode"]   = ESP.getFlashChipMode();
        doc["cpuFreqMHz"]  = ESP.getCpuFreqMHz();
        doc["sdkVersion"]  = ESP.getSdkVersion();
        doc["psramSize"]   = ESP.getPsramSize();
        doc["freePsram"]   = ESP.getFreePsram();
        doc["lastResetTime"] = esp_timer_get_time(); // Example: microseconds since startup
        
         // Add reset reason
        esp_reset_reason_t resetReason = esp_reset_reason();
        switch (resetReason) {
            case ESP_RST_POWERON: doc["resetReason"] = "Power-on Reset"; break;
            case ESP_RST_EXT:     doc["resetReason"] = "External Reset"; break;
            case ESP_RST_SW:      doc["resetReason"] = "Software Reset"; break;
            case ESP_RST_PANIC:   doc["resetReason"] = "Panic Reset"; break;
            case ESP_RST_INT_WDT: doc["resetReason"] = "Interrupt Watchdog Reset"; break;
            case ESP_RST_TASK_WDT:doc["resetReason"] = "Task Watchdog Reset"; break;
            case ESP_RST_WDT:     doc["resetReason"] = "Other Watchdog Reset"; break;
            case ESP_RST_DEEPSLEEP: doc["resetReason"] = "Deep Sleep Reset"; break;
            case ESP_RST_BROWNOUT: doc["resetReason"] = "Brownout Reset"; break;
            case ESP_RST_SDIO:    doc["resetReason"] = "SDIO Reset"; break;
            default:              doc["resetReason"] = "Unknown Reset"; break;
        }

        // Adding handler status
        // doc["enableWifiHandler"] = ENABLE_WIFI_HANDLER;
        // doc["enableWebHandler"] = ENABLE_WEB_HANDLER;
        // doc["enableImprovHandler"] = ENABLE_IMPROV_HANDLER;
        // doc["enableBluetoothHandler"] = ENABLE_BLUETOOTH_HANDLER;
        // doc["enableGfxHandler"] = ENABLE_GFX_HANDLER;
        // doc["enableButtonHandler"] = ENABLE_BUTTON_HANDLER;
        // doc["enableLedHandler"] = ENABLE_LED_HANDLER;
        // doc["enableRemoteDebugHandler"] = ENABLE_REMOTE_DEBUG_HANDLER;
        // doc["enableMqttHandler"] = ENABLE_MQTT_HANDLER;
        // doc["enableEzTimeHandler"] = ENABLE_EZTIME_HANDLER;

        WebHandler::sendSuccessResponse(request, "GET /device/get", &doc); });
}

void ServeDevice::handleDeviceReboot(AsyncWebServer &server)
{
    server.on("/device/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        
        debugV("Received GET request on /device/reboot");

        JsonDocument data;
        data["message"] = "Rebooting device";
        data["success"] = true;

        WebHandler::sendSuccessResponse(request, "GET /device/reboot", &data); 
        
        if (delayTimer.isReady())
        {
            ESP.restart();
        } });
}

void ServeDevice::handleDeviceWifiNetworks(AsyncWebServer &server)
{
    server.on("/device/wifi/networks", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        const char *filePath = "/wifi_networks.json";

        if (!LittleFS.begin(true)) {
            debugE("Failed to mount LittleFS");
            WebHandler::sendErrorResponse(request, 500, "Failed to mount filesystem");
            return;
        }

        File file = LittleFS.open(filePath, "r");
        if (!file) {
            debugE("Failed to open file %s for reading", filePath);
            WebHandler::sendErrorResponse(request, 500, "Failed to open network scan results");
            return;
        }

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, file);
        file.close();

        if (error) {
            debugE("Failed to parse JSON from file %s", filePath);
            WebHandler::sendErrorResponse(request, 500, "Failed to parse network scan results");
            return;
        }

        WebHandler::sendSuccessResponse(request, "GET /device/wifi/networks", &doc); });
}

#endif // ENABLE_WEB_HANDLER