#pragma once

#ifdef ENABLE_WEB_HANDLER

#include "Globals.h"
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "WebHandler.h"

class ServeFiles {
public:
    static void registerEndpoints(AsyncWebServer &server);

private:
    static void handleCreateFolder(AsyncWebServerRequest *request);
    static void handleDeleteFolder(AsyncWebServerRequest *request);
    static bool deleteFolderRecursive(const String &folderPath);
    static bool ensureParentDirsExist(const String &filePath);
    static void listFilesRecursive(JsonArray &files, const String &path);
    static void handleListFiles(AsyncWebServerRequest *request);
    static void handleReadFile(AsyncWebServerRequest *request);
    static void handleWriteFile(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    static bool isProtectedFile(const String &filename);
    static void handleDeleteFile(AsyncWebServerRequest *request);
};

#endif // ENABLE_WEB_HANDLER
