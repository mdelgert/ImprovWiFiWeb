#ifndef SERVE_FILES_H
#define SERVE_FILES_H

#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "WebHandler.h"

class ServeFiles {
public:
    static void registerEndpoints(AsyncWebServer &server);

private:
    static void handleListFiles(AsyncWebServerRequest *request);
    static void handleReadFile(AsyncWebServerRequest *request);
    static void handleWriteFile(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    static void handleDeleteFile(AsyncWebServerRequest *request);
    static bool ensureParentDirsExist(const String &filePath); // Helper to ensure directories exist
    static void listFilesRecursive(JsonArray &files, const String &path); // Recursive helper for listing files
};

#endif // SERVE_FILES_H
