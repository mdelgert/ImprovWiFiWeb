#ifdef ENABLE_TIME_HANDLER

#include "TimeHandler.h"
#include "TimeZones.h"
#include <time.h>
#include "NonBlockingTimer.h"

// Timers for resync and periodic updates
static NonBlockingTimer timeSyncTimer(60000);
static NonBlockingTimer timeTimer(1000);
static bool isTimeSynced = false;

// NTP servers
static const char* ntpServer1 = "pool.ntp.org";
static const char* ntpServer2 = "time.nist.gov";

// Default region hardcoded
static const char* defaultRegion = "America/New_York";

// Dynamically set offsets
static long gmtOffset_sec = 0;
static int daylightOffset_sec = 0;

void TimeHandler::init() {
    debugI("TimeHandler initialized");

    // Get POSIX string for the default region
    const char* posix_str = tz_db_get_posix_str(defaultRegion);
    if (!posix_str) {
        debugE("TimeHandler: Failed to find POSIX string for region %s", defaultRegion);
        return;
    }
    debugI("TimeHandler: Found POSIX string: %s", posix_str);

    // Parse offsets
    if (!parsePosixOffsets(posix_str, &gmtOffset_sec, &daylightOffset_sec)) {
        debugE("TimeHandler: Failed to parse offsets from POSIX string: %s", posix_str);
        return;
    }
    debugI("TimeHandler: Parsed offsets - gmtOffset_sec: %ld, daylightOffset_sec: %d", gmtOffset_sec, daylightOffset_sec);

    // Configure time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    syncTime();
}

void TimeHandler::loop() {
    if (!isTimeSynced) {
        syncTime();
    }

    if (timeSyncTimer.isReady()) {
        debugI("TimeHandler: Resyncing time...");
        syncTime();
    }

    if (timeTimer.isReady()) {
        debugD("TimeHandler: Current time: %s", getFormattedTime());
    }
}

void TimeHandler::syncTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        debugW("TimeHandler: Failed to obtain time");
        return;
    }

    debugI("TimeHandler: Time successfully synchronized. Current local time: %s", getFormattedTime());
    debugD("TimeHandler: DST flag (tm_isdst): %d", timeinfo.tm_isdst);

    isTimeSynced = true;
}

const char* TimeHandler::getFormattedTime() {
    static char timeString[64];
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        strcpy(timeString, "Time not set");
        return timeString;
    }
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return timeString;
}

/**
 * Parses the gmtOffset_sec and daylightOffset_sec from a POSIX timezone string.
 * Example POSIX string: "EST5EDT,M3.2.0,M11.1.0"
 */
bool TimeHandler::parsePosixOffsets(const char* posixStr, long* gmtOffset, int* daylightOffset) {
    if (!posixStr || !gmtOffset || !daylightOffset) {
        return false;
    }

    // Parse the GMT offset (e.g., "EST5" -> 5 * 3600)
    const char* gmtStart = strchr(posixStr, 'T');
    if (!gmtStart) {
        return false;
    }
    *gmtOffset = -(atoi(gmtStart + 1) * 3600); // Negative because POSIX strings specify offsets as positive

    // Look for daylight saving offset (EDT)
    const char* daylightStart = strchr(posixStr, ',');
    if (daylightStart) {
        *daylightOffset = 3600; // Default to 1 hour if DST is specified
    } else {
        *daylightOffset = 0; // No DST
    }

    return true;
}

#endif // ENABLE_TIME_HANDLER
