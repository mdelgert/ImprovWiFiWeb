#include "RemoteDebugHandler.h"

// Define the global Debug object
RemoteDebug Debug;

void RemoteDebugHandler::init()
{
    Serial.begin(115200);           // Start the serial communication

    //#############################################
    // This might be interfereing with ImprovWifi during setup...........................
    Debug.setSerialEnabled(true);   // Enable sending to serial debug as well (may want to disable it for release)
    //#############################################

    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true);         // Enable colors
}

void RemoteDebugHandler::loop()
{
    Debug.handle(); // Handles RemoteDebug commands
    yield();        // Give a time for ESP
}