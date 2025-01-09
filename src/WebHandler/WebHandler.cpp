// WebHandler.cpp
#include "WebHandler.h"

NonBlockingTimer WebHandler::myTimer(1000);
AsyncWebServer WebHandler::server(80);

void WebHandler::serveNotFound()
{
    server.onNotFound([](AsyncWebServerRequest *request){
        if (request->method() == HTTP_OPTIONS) { // Handle preflight CORS request
            AsyncWebServerResponse *response = request->beginResponse(204); // No Content
            WebHandler::addCorsHeaders(response); // Add generic CORS headers
            request->send(response);
            debugI("Handled CORS preflight request");
        } else { // Handle other unmatched routes
            request->send(404, "text/plain", "Not found");
            debugI("Route not found: %s", request->url().c_str());
        } });
}

void WebHandler::printRequestBody(AsyncWebServerRequest *request, uint8_t *data, size_t len)
{
    String requestBody = "";
    for (size_t i = 0; i < len; i++)
    {
        requestBody += (char)data[i];
    }
    debugI("Request Body: %s", requestBody.c_str());
}

bool WebHandler::isTokenValid(AsyncWebServerRequest *request)
{
    if (!ENABLE_API_TOKEN) return true;
    if (request->hasHeader("Authorization"))
    {
        AsyncWebHeader *header = request->getHeader("Authorization");
        if (String(header->value()) == String("Bearer ") + API_TOKEN)
        {
            return true;
        }
    }
    debugE("Invalid token");
    return false;
}

void WebHandler::addCorsHeaders(AsyncWebServerResponse *response)
{
    if (ENABLE_SECURE_CORS) return;
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

void WebHandler::sendErrorResponse(AsyncWebServerRequest *request, int statusCode, const char *message, bool checkToken)
{
    if (checkToken && !isTokenValid(request))
    {
        debugE("Token validation failed for error response");
        statusCode = 403; // Override status code for forbidden
        message = "Forbidden: Invalid token";
    }

    JsonDocument doc;
    doc["status"] = "error";
    doc["message"] = message;
    
    String jsonResponse;
    serializeJson(doc, jsonResponse);

    AsyncWebServerResponse *response = request->beginResponse(statusCode, "application/json", jsonResponse);
    addCorsHeaders(response);
    request->send(response);
}

void WebHandler::sendSuccessResponse(AsyncWebServerRequest *request, const char *message, JsonDocument *data, bool checkToken)
{
    if (checkToken && !isTokenValid(request))
    {
        debugE("Token validation failed for success response");
        sendErrorResponse(request, 403, "Forbidden: Invalid token", false);
        return;
    }

    JsonDocument doc;
    doc["status"] = "success";
    doc["message"] = message;

    if (data != nullptr)
    {
        doc["data"] = *data;
    }

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", jsonResponse);
    addCorsHeaders(response);
    request->send(response);
}

void WebHandler::init()
{
    if (!ENABLE_WEBHANDLER) return;

    while (WiFi.status() != WL_CONNECTED)
    {
        if (myTimer.isReady())
        {
            debugI("WebHandler waiting for WiFi...");
            break;
        }
    }

    ServeEmbedded::registerEndpoints(server);
    ServeDevice::registerEndpoints(server);
    ServeSettings::registerEndpoints(server);
    ServeActions::registerEndpoints(server);
    serveNotFound();
    server.begin();
    debugI("WebHandler initialized");
}

void WebHandler::loop()
{
    // debugI("WebHandler loop");
}