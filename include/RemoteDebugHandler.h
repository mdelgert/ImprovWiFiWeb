#ifndef REMOTE_DEBUG_HANDLER_H
#define REMOTE_DEBUG_HANDLER_H

// Disable WebSockets in RemoteDebug
//#define WEBSOCKET_DISABLED
// Exmple host if enabled host.local:8232

#include "Globals.h"
#include <RemoteDebug.h>

// Remote debug instance
extern RemoteDebug Debug;

class RemoteDebugHandler
{
public:
    static void init();
    static void loop();
    static void startNetwork();
};

#endif
