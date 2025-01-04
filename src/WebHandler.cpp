#include "WebHandler.h"

NonBlockingTimer WebHandler::myTimer(1000);
AsyncWebServer WebHandler::server(80);

void WebHandler::init()
{
    debugI("WebHandler initialized");

    while (WiFi.status() != WL_CONNECTED)
    {
        if (myTimer.isReady())
        {
            debugI("WebHandler waiting for WiFi...");
        }
    }

    // Serve embedded index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        size_t fileSize = index_html_end - index_html_start;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        request->send(response); });

    // Serve embedded device.html
    server.on("/device.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        size_t fileSize = device_html_end - device_html_start;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", device_html_start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        request->send(response); });

    // Serve embedded settings.html
    server.on("/settings.html", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        size_t fileSize = settings_html_end - settings_html_start;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", settings_html_start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        request->send(response); });

    // Serve embedded styles.css
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        size_t fileSize = styles_css_end - styles_css_start;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", styles_css_start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        request->send(response); });

    // Serve embedded script.js
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        size_t fileSize = script_js_end - script_js_start;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "application/javascript", script_js_start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        request->send(response); });

    server.begin();
    debugI("WebHandler waiting for webrequests.");
}

void WebHandler::loop()
{
    // No code needed for AsyncWebServer
    // debugI("WebHandler loop");
}
