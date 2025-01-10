#include "RemoteDebugHandler.h"

RemoteDebug Debug;

void RemoteDebugHandler::init()
{
    if(!settings.enableRemoteDebug) return;
    Serial.begin(115200);           // This might interfere with ImprovWifi because sending serial messages at the same time
    Debug.setSerialEnabled(true);   // Enable sending to serial debug as well (may want to disable it for release)
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true);       // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true);         // Enable colors
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