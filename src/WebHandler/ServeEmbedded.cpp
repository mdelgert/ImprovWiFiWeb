#ifdef ENABLE_WEB_HANDLER

#include "ServeEmbedded.h"

void ServeEmbedded::registerEndpoints(AsyncWebServer &server)
{
    handleGetRequest(server);
}

void ServeEmbedded::serveEmbeddedFile(AsyncWebServer &server, const char *path, const uint8_t *start, const uint8_t *end, const char *contentType)
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

void ServeEmbedded::handleGetRequest(AsyncWebServer &server)
{
    serveEmbeddedFile(server, "/actions.html", actions_html_start, actions_html_end, "text/html");
    serveEmbeddedFile(server, "/actions.js", actions_js_start, actions_js_end, "application/javascript");
    serveEmbeddedFile(server, "/advanced.html", advanced_html_start, advanced_html_end, "text/html");
    serveEmbeddedFile(server, "/advanced.js", advanced_js_start, advanced_js_end, "application/javascript");
    serveEmbeddedFile(server, "/blueserial.html", blueserial_html_start, blueserial_html_end, "text/html");
    serveEmbeddedFile(server, "/blueserial.js", blueserial_js_start, blueserial_js_end, "application/javascript");
    serveEmbeddedFile(server, "/error.html", error_html_start, error_html_end, "text/html");
    serveEmbeddedFile(server, "/favicon.ico", favicon_ico_start, favicon_ico_end, "image/x-icon");
    serveEmbeddedFile(server, "/footer.html", footer_html_start, footer_html_end, "text/html");
    serveEmbeddedFile(server, "/global.js", global_js_start, global_js_end, "application/javascript");
    serveEmbeddedFile(server, "/", index_html_start, index_html_end, "text/html");
    serveEmbeddedFile(server, "/index.js", index_js_start, index_js_end, "application/javascript");
    serveEmbeddedFile(server, "/navbar.html", navbar_html_start, navbar_html_end, "text/html");
    serveEmbeddedFile(server, "/settings.html", settings_html_start, settings_html_end, "text/html");
    serveEmbeddedFile(server, "/settings.js", settings_js_start, settings_js_end, "application/javascript");
    serveEmbeddedFile(server, "/styles.css", styles_css_start, styles_css_end, "text/css");
    serveEmbeddedFile(server, "/terminal.css", terminal_css_start, terminal_css_end, "text/css");
    serveEmbeddedFile(server, "/terminal.html", terminal_html_start, terminal_html_end, "text/html");
    serveEmbeddedFile(server, "/terminal.js", terminal_js_start, terminal_js_end, "application/javascript");
    serveEmbeddedFile(server, "/timezones.json", timezones_json_start, timezones_json_end, "application/json");

    debugI("ServeEmbedded handleGetRequest registered");
}

#endif // ENABLE_WEB_HANDLER