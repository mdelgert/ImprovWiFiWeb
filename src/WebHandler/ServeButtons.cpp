#include "ServeButtons.h"

// Define the file path for the buttons JSON file
const char *ServeButtons::BUTTONS_FILE = "/buttons2.json";

void ServeButtons::registerEndpoints(AsyncWebServer &server)
{
    server.on("/buttons", HTTP_GET, handleGetButtons);
    server.on("/buttons", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, handlePostButtons);
    server.on("/buttons/{id}", HTTP_DELETE, handleDeleteButton);
}

void ServeButtons::handleGetButtons(AsyncWebServerRequest *request)
{
    // Open the file for reading
    File file = LittleFS.open(BUTTONS_FILE, "r");
    if (!file || file.size() == 0) {
        request->send(500, "application/json", "{\"error\":\"Failed to read buttons2.json or file is empty\"}");
        return;
    }

    String json = file.readString(); // Read the file content into a string
    file.close(); // Close the file

    request->send(200, "application/json", json); // Send the file content as JSON
}

void ServeButtons::handleDeleteButton(AsyncWebServerRequest *request)
{
    if (!request->hasParam("id")) {
        request->send(400, "application/json", "{\"error\":\"Missing button ID\"}");
        return;
    }

    int buttonId = request->getParam("id")->value().toInt();

    // Open the existing file for reading
    File file = LittleFS.open(BUTTONS_FILE, "r");
    if (!file) {
        request->send(500, "application/json", "{\"error\":\"Failed to read buttons2.json\"}");
        return;
    }

    JsonDocument doc;
    deserializeJson(doc, file); // Deserialize existing data
    file.close();

    JsonArray buttons = doc["buttons"];
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i]["id"] == buttonId) {
            buttons.remove(i); // Remove the button
            break;
        }
    }

    // Write the updated JSON back to the file
    file = LittleFS.open(BUTTONS_FILE, "w");
    if (!file) {
        request->send(500, "application/json", "{\"error\":\"Failed to write buttons2.json\"}");
        return;
    }
    serializeJson(doc, file); // Write the updated JSON
    file.close();

    request->send(200, "application/json", "{\"message\":\"Button deleted successfully\"}");
}

void ServeButtons::handlePostButtons(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    debugV("Received POST request on /buttons");

    if (index == 0) {
        // Open the file for writing at the start of the upload
        debugV("Starting new JSON file upload");
        File file = LittleFS.open(BUTTONS_FILE, "w");
        if (!file) {
            debugE("Failed to open file for writing: %s", BUTTONS_FILE);
            WebHandler::sendErrorResponse(request, 500, "Failed to open file for writing");
            return;
        }
        file.close(); // Close immediately to ensure the file is ready for appending chunks
    }

    // Append data chunk to the file
    File file = LittleFS.open(BUTTONS_FILE, "a");
    if (!file) {
        debugE("Failed to open file for appending: %s", BUTTONS_FILE);
        WebHandler::sendErrorResponse(request, 500, "Failed to open file for appending");
        return;
    }
    file.write(data, len);
    file.close();
    debugV("Data chunk written to file: %d bytes", len);

    if (index + len == total) {
        debugV("Completed JSON file upload");
        WebHandler::sendSuccessResponse(request, "Buttons updated successfully");
    }
}
