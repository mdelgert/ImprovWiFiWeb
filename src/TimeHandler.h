#pragma once

#ifdef ENABLE_TIME_HANDLER

#include "Globals.h"
#include "TimeZones.h"
#include "NonBlockingTimer.h"
#include <time.h>

/**
 * TimeHandler is responsible for setting up NTP time synchronization
 * and providing access to the current local time.
 */
class TimeHandler
{
private:
    static void syncTime();
    static bool parsePosixOffsets(const char* posixStr, long* gmtOffset, int* daylightOffset);
    
public:
    /**
     * init() is called once at startup to configure NTP and any offsets.
     */
    static void init();

    /**
     * loop() is called frequently to allow periodic maintenance, e.g. re-sync.
     */
    static void loop();

    /**
     * Returns a const char* with the formatted local time (thread-safe usage pattern).
     */
    static const char* getFormattedTime();
};

#else

/**
 * No-op implementation if ENABLE_TIME_HANDLER is not defined.
 * This allows other code to compile without changing references.
 */
class TimeHandler
{ 
public:
    static void init() {}
    static void loop() {}
    static const char* getFormattedTime() { return ""; }
};

#endif // ENABLE_TIME_HANDLER
