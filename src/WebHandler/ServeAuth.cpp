#ifdef ENABLE_WEB_HANDLER

#include "ServeAuth.h"
#include "Globals.h"
#include "WebHandler.h"
#include <ArduinoJson.h>

void ServeAuth::registerEndpoints(AsyncWebServer &server)
{
    handleLoginRequest(server);
}

void ServeAuth::handleLoginRequest(AsyncWebServer &server)
{
    server.on("/auth/login", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
        debugV("Received POST request on /auth/login");

        WebHandler::printRequestBody(request, data, len);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, data, len);

        if (error) {
            debugE("JSON deserialization failed: %s", error.c_str());
            request->send(400, "application/json", R"({"status": "error", "message": "Invalid JSON payload"})");
            return;
        }

        const char* username = doc["username"] | "";
        const char* password = doc["password"] | "";

        debugV("Attempting login: username=%s", username);

        if (strcmp(username, "admin") == 0 && strcmp(password, "pass") == 0) {
            String sessionToken = "example_session_12345";

            JsonDocument response;
            response["status"] = "success";
            response["message"] = "Login successful";
            response["data"]["token"] = sessionToken;

            String jsonResponse;
            serializeJson(response, jsonResponse);

            AsyncWebServerResponse *res = request->beginResponse(200, "application/json", jsonResponse);
            res->addHeader("Set-Cookie", "session=" + sessionToken + "; Path=/; HttpOnly;");
            request->send(res);
        } else {
            request->send(401, "application/json", R"({"status": "error", "message": "Invalid credentials"})");
        }
    });
}

#endif // ENABLE_WEB_HANDLER
