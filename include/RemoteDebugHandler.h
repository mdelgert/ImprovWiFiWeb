#ifndef REMOTE_DEBUG_HANDLER_H
#define REMOTE_DEBUG_HANDLER_H

// Disable WebSockets in RemoteDebug
//#define WEBSOCKET_DISABLED
// Exmple host if enabled host.local:8232

#include "Globals.h"
#include <RemoteDebug.h>
#include "GfxHandler.h"
#include "LedHandler.h"

// Remote debug instance
extern RemoteDebug Debug;

class RemoteDebugHandler
{
public:
    static void loop();
    static void startNetwork();
    static void init();
private:
    static void handleCustomCommands();
};

#endif
