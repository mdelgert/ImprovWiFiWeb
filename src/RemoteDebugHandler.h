#ifndef REMOTE_DEBUG_HANDLER_H
#define REMOTE_DEBUG_HANDLER_H

#ifdef ENABLE_REMOTE_DEBUG_HANDLER
#include "Globals.h"
#include <RemoteDebug.h>
#include "GfxHandler.h"
#include "LedHandler.h"

// Declare the RemoteDebug instance
extern RemoteDebug Debug;

class RemoteDebugHandler {
public:
    static void loop();
    static void startNetwork();
    static void init();

private:
    static void handleCustomCommands();
};

#else

// No-op implementation of RemoteDebugHandler
#define debugA(...)
#define debugP(...)
#define debugV(...)
#define debugD(...)
#define debugI(...)
#define debugW(...)
#define debugE(...)
class RemoteDebugHandler {
public:
    static void loop() {}           // No-op
    static void startNetwork() {}   // No-op
    static void init() {}           // No-op
};

#endif // ENABLE_REMOTE_DEBUG_HANDLER

#endif // REMOTE_DEBUG_HANDLER_H