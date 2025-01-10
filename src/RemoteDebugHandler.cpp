#include "RemoteDebugHandler.h"

RemoteDebug Debug;

// Store the custom command handling logic in a global or class-level function
void handleCustomCommands() {
    String command = Debug.getLastCommand(); // Retrieve the last received command
    if (command == "clear") {
        Debug.println("\033[2J\033[H"); // Send ANSI escape codes to clear the terminal
    } else {
        Debug.println("Unknown command");
    }
}

void RemoteDebugHandler::init()
{
    if(!settings.enableRemoteDebug) return;
    Serial.begin(115200);           // This might interfere with ImprovWifi because sending serial messages at the same time
    Debug.setSerialEnabled(true);   // Enable sending to serial debug as well (may want to disable it for release)
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true);         // Enable colors

    // Add a custom command for "clear"
    Debug.setHelpProjectsCmds("clear - Clear the terminal"); // Add help text
    Debug.setCallBackProjectCmds(handleCustomCommands);      // Use the global function as the callback
}

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