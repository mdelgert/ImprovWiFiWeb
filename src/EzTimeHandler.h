#ifndef EZTIME_HANDLER_H
#define EZTIME_HANDLER_H

#ifdef ENABLE_EZTIME_HANDLER

#include "Globals.h"

/**
 * EzTimeHandler uses the ezTime library to automatically handle
 * NTP time synchronization, time zones, and DST.
 */
class EzTimeHandler
{
private:
    // Private helper to do an on-demand sync (or re-sync).
    static void syncTime();

public:
    // Set up ezTime (e.g., set location/region, do initial NTP sync).
    static void init();

    // Called periodically; ezTime needs `events()` to keep tasks updated.
    static void loop();

    // Return a string with the current local time.
    static const char* getFormattedTime();
};

#else

/**
 * No-op version of EzTimeHandler if ENABLE_EZTIME_HANDLER is undefined
 * (allows your code to compile without changes if you're not using ezTime).
 */
class EzTimeHandler
{ 
public:
    static void init() {}
    static void loop() {}
    static const char* getFormattedTime() { return ""; }
};

#endif // ENABLE_EZTIME_HANDLER
#endif // EZTIME_HANDLER_H
