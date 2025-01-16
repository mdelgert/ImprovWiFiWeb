#include "ServeFiles.h"

// Register endpoints for file management
void ServeFiles::registerEndpoints(AsyncWebServer &server) {
    server.on("/files", HTTP_GET, handleListFiles);           // List files
    server.on("/file", HTTP_GET, handleReadFile);             // Read a file
    server.on("/file", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, handleWriteFile); // Write a file
    server.on("/file", HTTP_DELETE, handleDeleteFile);        // Delete a file
}

// Helper to ensure parent directories exist
bool ServeFiles::ensureParentDirsExist(const String &filePath) {
    int lastSlashIndex = filePath.lastIndexOf('/');
    if (lastSlashIndex <= 0) return true; // No parent directories

    String parentPath = filePath.substring(0, lastSlashIndex);
    debugV("Ensuring directory exists: %s", parentPath.c_str());

    if (LittleFS.exists(parentPath)) return true; // Directory already exists
    return LittleFS.mkdir(parentPath);           // Create the directory
}

// Recursive helper for listing files
void ServeFiles::listFilesRecursive(JsonArray &files, const String &path) {
    // Ensure the directory path starts with "/" and does not end with "/"
    String dirPath = path.isEmpty() ? "/" : (path.endsWith("/") ? path : path + "/");

    debugV("Opening directory: %s", dirPath.c_str());
    File dir = LittleFS.open(dirPath);

    if (!dir || !dir.isDirectory()) {
        debugE("Failed to open directory: %s", dirPath.c_str());
        return;
    }

    File file = dir.openNextFile();
    while (file) {
        String fullPath = dirPath + file.name();

        if (file.isDirectory()) {
            debugV("Entering directory: %s", fullPath.c_str());
            // Recursively list files in subdirectory
            listFilesRecursive(files, fullPath);
        } else {
            debugV("Found file: %s", fullPath.c_str());
            files.add(fullPath);
        }

        file = dir.openNextFile();
    }
}

// Handle listing files
void ServeFiles::handleListFiles(AsyncWebServerRequest *request) {
    debugV("Received GET request on /files");

    // DynamicJsonDocument doc(4096);
    // JsonArray files = doc["files"].to<JsonArray>();
    JsonDocument doc;
    JsonArray files = doc["files"].to<JsonArray>();

    // Start recursive listing from the root directory
    listFilesRecursive(files, "/");

    WebHandler::sendSuccessResponse(request, "Files listed successfully", &doc);
}

// Handle reading a file
void ServeFiles::handleReadFile(AsyncWebServerRequest *request) {
    debugV("Received GET request on /file");

    if (!request->hasParam("filename")) {
        debugE("Missing filename parameter");
        WebHandler::sendErrorResponse(request, 400, "Filename is required");
        return;
    }
    String filename = request->getParam("filename")->value();
    debugV("Requested file: %s", filename.c_str());

    if (!LittleFS.exists(filename)) {
        debugE("File not found: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 404, "File not found");
        return;
    }

    File file = LittleFS.open(filename, "r");
    if (!file) {
        debugE("Failed to open file: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 500, "Failed to open file");
        return;
    }

    String content = file.readString();
    file.close();
    debugV("File content: %s", content.c_str());

    //request->send(200, "text/plain", content);

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", content);
    WebHandler::addCorsHeaders(response);
    request->send(response);
}

// Handle writing to a file
void ServeFiles::handleWriteFile(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    debugV("Received POST request on /file");

    if (!request->hasParam("filename")) {
        WebHandler::sendErrorResponse(request, 400, "Filename is required");
        return;
    }
    String filename = request->getParam("filename")->value();
    debugV("Filename: %s", filename.c_str());

    // Ensure parent directories exist
    if (!ensureParentDirsExist(filename)) {
        debugE("Failed to create parent directories for: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 500, "Failed to create directories");
        return;
    }

    debugV("Data length: %d, Index: %d, Total: %d", len, index, total);

    File file = LittleFS.open(filename, index == 0 ? "w" : "a");
    if (!file) {
        debugE("Failed to open file for writing: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 500, "Failed to open file for writing");
        return;
    }

    file.write(data, len);
    file.close();
    debugV("Data written to file: %s", filename.c_str());

    if (index + len == total) {
        WebHandler::sendSuccessResponse(request, "File saved successfully");
    }
}

// Check if a file is protected
bool ServeFiles::isProtectedFile(const String &filename) {
    static const char *protectedFiles[] = {
        //"/settings.json",
        //"/wifi_networks.json",
        //"/test.txt"
    };

    for (const char *protectedFile : protectedFiles) {
        if (filename == protectedFile) return true;
    }
    return false;
}

// Handle deleting a file
void ServeFiles::handleDeleteFile(AsyncWebServerRequest *request) {
    debugV("Received DELETE request on /file");

    if (!request->hasParam("filename")) {
        debugE("Missing filename parameter");
        WebHandler::sendErrorResponse(request, 400, "Filename is required");
        return;
    }
    String filename = request->getParam("filename")->value();
    debugV("Filename to delete: %s", filename.c_str());

    if (isProtectedFile(filename)) {
        debugE("Cannot delete protected file: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 403, "Cannot delete protected file: %s", filename.c_str());
        //WebHandler::sendErrorResponse(request, 403, "Cannot modify protected file");
        return;
    }
    
    if (LittleFS.remove(filename)) {
        debugV("File deleted: %s", filename.c_str());
        WebHandler::sendSuccessResponse(request, "File deleted successfully");
    } else {
        debugE("Failed to delete file: %s", filename.c_str());
        WebHandler::sendErrorResponse(request, 500, "Failed to delete file");
    }
}
