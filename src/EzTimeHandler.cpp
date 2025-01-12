#ifdef ENABLE_EZTIME_HANDLER

#include "EzTimeHandler.h"
#include <ezTime.h>           // Make sure to install ropg/ezTime
#include "NonBlockingTimer.h" // Your timer utility (if you need periodic sync)

static Timezone myTZ;
static bool     isTimeSynced = false;
static char     timeString[64];

// Example: re-sync every 60 seconds (adjust as needed).
static NonBlockingTimer syncTimer(60000);
static NonBlockingTimer msgTimer(1000);

void EzTimeHandler::init()
{
    debugI("EzTimeHandler initialized");

    // 1) Set your time zone location (handles DST automatically if region supports it).
    //    Check https://github.com/ropg/ezTime/blob/master/examples/Example13-Timezones/zoneList.txt
    //    for valid strings (e.g., "America/New_York", "Europe/Berlin", etc.).
    myTZ.setLocation(F("America/New_York"));

    // 2) Attempt an immediate time sync
    syncTime();
}

void EzTimeHandler::loop()
{
    // ezTime needs events() called periodically
    events();

    // If time has never been synced, keep trying until success
    if (!isTimeSynced) {
        syncTime();
    }

    // Periodically re-sync using your NonBlockingTimer
    if (syncTimer.isReady()) {
        debugI("EzTimeHandler: Performing periodic re-sync");
        syncTime();
    }

    if(msgTimer.isReady()) {
        debugI("EzTimeHandler: Local time is now: %s", getFormattedTime());
    }
}

/**
 * syncTime() calls ezTime's global updateNTP() (which has no return value).
 * We then check timeStatus() to see if time was set.
 */
void EzTimeHandler::syncTime()
{
    // updateNTP() triggers an NTP request in the background.
    // You can then check timeStatus() to see if it's timeSet, timeNeedsSync, or timeNotSet.
    updateNTP();

    if (timeStatus() == timeSet) {
        // We have valid time now.
        isTimeSynced = true;
        debugI("EzTimeHandler: NTP sync successful. Local time is now: %s", getFormattedTime());
        debugI("EzTimeHandler: DST active? %s", myTZ.isDST() ? "Yes" : "No");
        debugI("EzTimeHandler: UTC offset (seconds): %d", myTZ.getOffset());
    } else {
        debugW("EzTimeHandler: NTP sync attempt failed or pending (timeStatus != timeSet).");
    }
}

/**
 * Returns a string representing the current local time in the format "YYYY-MM-DD HH:MM:SS".
 */
const char* EzTimeHandler::getFormattedTime()
{
    if (!isTimeSynced) {
        strcpy(timeString, "Time not synced");
        return timeString;
    }

    // Format date/time with ezTime. For example: "Y-m-d H:i:s" => "2025-01-11 18:45:30"
    // You can customize the format using standard strftime-like tokens:
    //   https://github.com/ropg/ezTime#formatting-and-parsing
    String formatted = myTZ.dateTime(F("Y-m-d H:i:s"));
    strncpy(timeString, formatted.c_str(), sizeof(timeString));
    timeString[sizeof(timeString) - 1] = '\0'; // Ensure null termination

    return timeString;
}

#endif // ENABLE_EZTIME_HANDLER
