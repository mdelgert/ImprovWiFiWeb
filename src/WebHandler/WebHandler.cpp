// WebHandler.cpp
#include "WebHandler.h"

NonBlockingTimer WebHandler::myTimer(1000);
AsyncWebServer WebHandler::server(80);
static String ssid, password;

void WebHandler::printRequestBody(AsyncWebServerRequest* request, uint8_t* data, size_t len) {
    String requestBody = "";
    for (size_t i = 0; i < len; i++) {
        requestBody += (char)data[i];
    }
    debugI("Request Body: %s", requestBody.c_str());
}

bool WebHandler::isTokenValid(AsyncWebServerRequest* request) {
    if (!ENABLE_API_TOKEN) return true;
    if (request->hasHeader("Authorization")) {
        AsyncWebHeader* header = request->getHeader("Authorization");
        if (String(header->value()) == String("Bearer ") + API_TOKEN) {
            return true;
        }
    }
    debugE("Invalid token");
    return false;
}

void WebHandler::addCorsHeaders(AsyncWebServerResponse* response) {
    if (ENABLE_SECURE_CORS) return;
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

void WebHandler::sendErrorResponse(AsyncWebServerRequest* request, int statusCode, const char* message, bool checkToken) {
    if (checkToken && !isTokenValid(request)) {
        debugE("Token validation failed for error response");
        statusCode = 403; // Override status code for forbidden
        message = "Forbidden: Invalid token";
    }

    JsonDocument doc;
    doc["status"] = "error";
    doc["message"] = message;

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    AsyncWebServerResponse* response = request->beginResponse(statusCode, "application/json", jsonResponse);
    addCorsHeaders(response);
    request->send(response);
}

void WebHandler::sendSuccessResponse(AsyncWebServerRequest* request, const char* message, JsonDocument* data, bool checkToken) {
    if (checkToken && !isTokenValid(request)) {
        debugE("Token validation failed for success response");
        sendErrorResponse(request, 403, "Forbidden: Invalid token", false);
        return;
    }

    JsonDocument doc;
    doc["status"] = "success";
    doc["message"] = message;

    if (data != nullptr) {
        doc["data"] = *data;
    }

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    AsyncWebServerResponse* response = request->beginResponse(200, "application/json", jsonResponse);
    addCorsHeaders(response);
    request->send(response);
}

void WebHandler::serveEmbeddedFile(const char *path, const uint8_t *start, const uint8_t *end, const char *contentType)
{
    server.on(path, HTTP_GET, [path, start, end, contentType](AsyncWebServerRequest *request)
              {
        size_t fileSize = end - start;
        AsyncWebServerResponse* response = request->beginResponse_P(200, contentType, start, fileSize);
        response->addHeader("Content-Encoding", "identity");
        WebHandler::addCorsHeaders(response);
        request->send(response);
        debugI("Served: %s", path); });
}

void WebHandler::init()
{
    if(!ENABLE_WEBHANDLER) return;
    
    debugI("WebHandler initialized");

    while (WiFi.status() != WL_CONNECTED)
    {
        if (myTimer.isReady())
        {
            debugI("WebHandler waiting for WiFi...");
            break;
        }
    }

    // Initialize LittleFS
    if (!LittleFS.begin(true))
    {
        debugE("Failed to mount LittleFS");
        return;
    }
    debugI("LittleFS mounted successfully");

    serveNotFound();
    serveRoot();
    serveActions();
    ServeSettings::registerEndpoints(server);
    ServeDevice::registerEndpoints(server);
    
    // Start the web server
    server.begin();
    debugI("Web server started!");
}

void WebHandler::loop()
{
    // debugI("WebHandler loop");
}

void WebHandler::serveRoot()
{
    serveEmbeddedFile("/actions.html", actions_html_start, actions_html_end, "text/html");
    serveEmbeddedFile("/actions.js", actions_js_start, actions_js_end, "application/javascript");
    serveEmbeddedFile("/advanced.html", advanced_html_start, advanced_html_end, "text/html");
    serveEmbeddedFile("/advanced.js", advanced_js_start, advanced_js_end, "application/javascript");
    serveEmbeddedFile("/footer.html", footer_html_start, footer_html_end, "text/html");
    serveEmbeddedFile("/global.js", global_js_start, global_js_end, "application/javascript");
    serveEmbeddedFile("/", index_html_start, index_html_end, "text/html");
    serveEmbeddedFile("/index.js", index_js_start, index_js_end, "application/javascript");
    serveEmbeddedFile("/navbar.html", navbar_html_start, navbar_html_end, "text/html");
    serveEmbeddedFile("/settings.html", settings_html_start, settings_html_end, "text/html");
    serveEmbeddedFile("/settings.js", settings_js_start, settings_js_end, "application/javascript");
    serveEmbeddedFile("/styles.css", styles_css_start, styles_css_end, "text/css");
    debugI("WebHandler handleRoot");
}

void WebHandler::serveActions()
{
    // Serve files from LittleFS
    server.on("/actions/save", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
        debugI("Received JSON payload on /actions/save");

        JsonDocument doc;

        // Parse the JSON data
        DeserializationError error = deserializeJson(doc, data, len);
        if (error) {
            debugE("Failed to parse JSON: %s", error.c_str());
            request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
            return;
        }

        // Convert JSON to a string
        String jsonString;
        serializeJson(doc, jsonString);

        // Save JSON to LittleFS
        File file = LittleFS.open("/actions.json", "w");
        if (!file) {
            debugE("Failed to open file for writing");
            request->send(500, "application/json", "{\"status\":\"error\",\"message\":\"Failed to save file\"}");
            return;
        }
        file.print(jsonString);
        file.close();

        debugI("JSON saved to /actions.json");
        AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{\"status\":\"success\",\"message\":\"File saved successfully\"}");
        WebHandler::addCorsHeaders(response);
        request->send(response); });

    // Serve JSON data
    server.on("/actions/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        File file = LittleFS.open("/actions.json", "r");
        if (!file) {
            debugE("Failed to open /actions.json");
            AsyncWebServerResponse *response = request->beginResponse(404, "application/json", "{\"status\":\"error\",\"message\":\"File not found\"}");
            WebHandler::addCorsHeaders(response);
            request->send(response);
            return;
        }

        String json = file.readString();
        file.close();
        debugI("Serving /actions.json");

        JsonDocument doc; // Use the simplified declaration
        DeserializationError error = deserializeJson(doc, json);
        if (error) {
            debugE("Failed to parse saved JSON: %s", error.c_str());
            request->send(500, "application/json", "{\"status\":\"error\",\"message\":\"Internal server error\"}");
            return;
        }

        // Convert JSON back to string for response
        String responseString;
        serializeJson(doc, responseString);

        AsyncWebServerResponse *response = request->beginResponse(200, "application/json", responseString);
        WebHandler::addCorsHeaders(response);
        request->send(response); });

    debugI("WebHandler serveActions");
}

void WebHandler::serveNotFound()
{
    server.onNotFound([](AsyncWebServerRequest *request)
    {
        if (request->method() == HTTP_OPTIONS) {
            // Handle preflight CORS request
            AsyncWebServerResponse *response = request->beginResponse(204); // No Content
            WebHandler::addCorsHeaders(response); // Add generic CORS headers
            request->send(response);
            debugI("Handled CORS preflight request");
        } else {
            // Handle other unmatched routes
            request->send(404, "text/plain", "Not found");
            debugI("Route not found: %s", request->url().c_str());
        }
    });
}
