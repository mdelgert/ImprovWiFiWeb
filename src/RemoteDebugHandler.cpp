#ifdef ENABLE_REMOTE_DEBUG_HANDLER

#include "RemoteDebugHandler.h"

RemoteDebug Debug;

void RemoteDebugHandler::loop()
{
    Debug.handle(); // Handles RemoteDebug commands
    yield();        // Give a time for ESP
}

void RemoteDebugHandler::startNetwork()
{
    Debug.begin(settings.deviceName);
}

void RemoteDebugHandler::init()
{
    Serial.begin(115200);           // This might interfere with ImprovWifi because sending serial messages at the same time
    //Debug.setSerialEnabled(true);   // Enable sending to serial debug as well (may want to disable it for release)
    //Debug.setResetCmdEnabled(true); // Enable the reset command
    //Debug.showTime(true);           // Show time in debug messages
    //Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
    //Debug.showColors(true);         // Enable colors
    //Debug.setPassword("");     // Set the password for the debug console
    Debug.setCallBackProjectCmds(handleCustomCommands); // Use the global function as the callback
}

// Store the custom command handling logic in a global or class-level function
void RemoteDebugHandler::handleCustomCommands() {
    String command = Debug.getLastCommand(); // Retrieve the last received command
    CommandHandler::handleCommand(command); // Pass the command to the CommandHandler
}

#endif // ENABLE_REMOTE_DEBUG_HANDLER