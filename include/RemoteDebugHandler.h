#ifndef REMOTE_DEBUG_HANDLER_H
#define REMOTE_DEBUG_HANDLER_H

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
