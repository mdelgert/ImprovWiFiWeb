#pragma once

#ifdef ENABLE_TIME_HANDLER

#include "Globals.h"
#include "GfxHandler.h"
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
    static void logAllDateTimeFormats();
    
public:
    static void init();
    static void loop();
    static long getLinuxTime();
    static const char* formatDateTime(const char* format);
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
    static long getLinuxTime() { return 0; }
    static const char* formatDateTime(const char* format) { return ""; }
};

#endif // ENABLE_TIME_HANDLER
