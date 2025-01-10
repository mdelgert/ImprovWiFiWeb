#include "RemoteDebugHandler.h"
#include "GfxHandler.h" // Include the GfxHandler header
#include "LedHandler.h" // Include the LedHandler header
#include <FastLED.h>    // For CRGB color definitions

RemoteDebug Debug;

void RemoteDebugHandler::loop()
{
    if(!settings.enableRemoteDebug) return;
    Debug.handle(); // Handles RemoteDebug commands
    yield();        // Give a time for ESP
}

void RemoteDebugHandler::startNetwork()
{
    if(!settings.enableRemoteDebug) return;
    Debug.begin(settings.deviceName);
}

void RemoteDebugHandler::init()
{
    if(!settings.enableRemoteDebug) return;
    Serial.begin(115200);           // This might interfere with ImprovWifi because sending serial messages at the same time
    Debug.setSerialEnabled(true);   // Enable sending to serial debug as well (may want to disable it for release)
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true);         // Enable colors

    // Add custom commands
    Debug.setHelpProjectsCmds(
        "clear - Clear the terminal\n"
        "hello - Print Hello, World!\n"
        "tft [YourMessage] - Display a message on the TFT\n"
        "led [YourColor] - Set LED color (e.g., Red, Green, Blue)"
    ); // Add help text for all commands
    Debug.setCallBackProjectCmds(handleCustomCommands); // Use the global function as the callback
}

// Store the custom command handling logic in a global or class-level function
void RemoteDebugHandler::handleCustomCommands() {
    String command = Debug.getLastCommand(); // Retrieve the last received command
    if (command.startsWith("clear")) {
        Debug.println("\033[2J\033[H"); // Send ANSI escape codes to clear the terminal
    } else if (command.startsWith("hello")) {
        Debug.println("Hello, World!"); // Print "Hello, World!" to the console
    } else if (command.startsWith("tft ")) { // Check if the command starts with "tft "
        String message = command.substring(4); // Extract the message after "tft "
        if (message.length() > 0) {
            GfxHandler::printMessage(message); // Call GfxHandler to print the message
            Debug.println("Message sent to TFT: " + message);
        } else {
            Debug.println("Error: No message provided. Usage: tft YourMessage");
        }
    } else if (command.startsWith("led ")) { // Check if the command starts with "led "
        String color = command.substring(4); // Extract the color after "led "
        if (color.length() > 0) {
            CRGB selectedColor;

            // Convert the color string to a CRGB value
            if (color.equalsIgnoreCase("Red")) {
                selectedColor = CRGB::Red;
            } else if (color.equalsIgnoreCase("Green")) {
                selectedColor = CRGB::Green;
            } else if (color.equalsIgnoreCase("Blue")) {
                selectedColor = CRGB::Blue;
            } else if (color.equalsIgnoreCase("Yellow")) {
                selectedColor = CRGB::Yellow;
            } else if (color.equalsIgnoreCase("Cyan")) {
                selectedColor = CRGB::Cyan;
            } else if (color.equalsIgnoreCase("Magenta")) {
                selectedColor = CRGB::Magenta;
            } else if (color.equalsIgnoreCase("White")) {
                selectedColor = CRGB::White;
            } else if (color.equalsIgnoreCase("Black")) {
                selectedColor = CRGB::Black;
            } else {
                Debug.println("Error: Invalid color. Supported colors are Red, Green, Blue, Yellow, Cyan, Magenta, White, and Black.");
                return;
            }

            LedHandler::setColor(selectedColor); // Set the LED color
            Debug.println("LED color set to: " + color);
        } else {
            Debug.println("Error: No color provided. Usage: led YourColor");
        }
    } else {
        Debug.println("Unknown command");
    }
}
