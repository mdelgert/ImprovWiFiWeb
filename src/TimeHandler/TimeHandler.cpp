#ifdef ENABLE_TIME_HANDLER

#include "TimeHandler.h"

// Default region hardcoded
//const char *defaultRegion = "Etc/Zulu";
const char *defaultRegion = "America/New_York";

// NTP servers the public rate limit (without an API key) is 5 requests in a rolling 30 second window;
// the rate limit with an API key is 50 requests in a rolling 30 second window. A query interval of
// 10 minutes or longer is generally acceptable for both services.

static const char *ntpServer1 = "pool.ntp.org";
static const char *ntpServer2 = "time.nist.gov";

// Dynamically set offsets
static long gmtOffset_sec = 0;
static int daylightOffset_sec = 0;

// Flag to indicate if time has been synchronized
static bool isTimeSynced = false;
//static NonBlockingTimer timeDelay(1000);

bool TimeHandler::getTimeSyncStatus()
{
    return isTimeSynced;
}

const char *TimeHandler::getDefaultRegion()
{
    return defaultRegion;
}

void TimeHandler::init()
{
    debugI("TimeHandler initialized using timezone: %s", defaultRegion);

    // Get POSIX string for the default region
    const char *posix_str = tz_db_get_posix_str(defaultRegion);
    if (!posix_str)
    {
        debugE("TimeHandler: Failed to find POSIX string for region %s", defaultRegion);
        return;
    }
    debugI("TimeHandler: Found POSIX string: %s", posix_str);

    // Parse offsets
    if (!parsePosixOffsets(posix_str, &gmtOffset_sec, &daylightOffset_sec))
    {
        debugE("TimeHandler: Failed to parse offsets from POSIX string: %s", posix_str);
        return;
    }
    debugI("TimeHandler: Parsed offsets - gmtOffset_sec: %ld, daylightOffset_sec: %d", gmtOffset_sec, daylightOffset_sec);

    // Configure time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    syncTime();
}

void TimeHandler::loop()
{
    if (!isTimeSynced)
    {
        syncTime();
        // if (timeDelay.isReady())
        // {
        //     debugI("TimeHandler: Resyncing time...");
        //     syncTime();
        // }
    }
}

void TimeHandler::syncTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        debugW("TimeHandler: Failed to obtain time");
        return;
    }

    debugI("TimeHandler: Time successfully synchronized. Current local time: %s", formatDateTime("%Y-%m-%d %I:%M:%S %p"));
    // debugD("TimeHandler: DST flag (tm_isdst): %d", timeinfo.tm_isdst);

    isTimeSynced = true;
}

/**
 * Parses the gmtOffset_sec and daylightOffset_sec from a POSIX timezone string.
 * Example POSIX string: "EST5EDT,M3.2.0,M11.1.0"
 */
bool TimeHandler::parsePosixOffsets(const char *posixStr, long *gmtOffset, int *daylightOffset)
{
    if (!posixStr || !gmtOffset || !daylightOffset)
    {
        return false;
    }

    // Parse the GMT offset (e.g., "EST5" -> 5 * 3600)
    const char *gmtStart = strchr(posixStr, 'T');
    if (!gmtStart)
    {
        return false;
    }
    *gmtOffset = -(atoi(gmtStart + 1) * 3600); // Negative because POSIX strings specify offsets as positive

    // Look for daylight saving offset (EDT)
    const char *daylightStart = strchr(posixStr, ',');
    if (daylightStart)
    {
        *daylightOffset = 3600; // Default to 1 hour if DST is specified
    }
    else
    {
        *daylightOffset = 0; // No DST
    }

    return true;
}

long TimeHandler::getLinuxTime()
{
    return time(nullptr); // Returns the current time as seconds since epoch
}

String TimeHandler::formatDateTime(const char *format, time_t timestamp)
{
    struct tm timeinfo;

    // Use the provided timestamp, or fall back to the current time
    time_t timeToFormat = (timestamp != 0) ? timestamp : time(nullptr);

    if (timeToFormat < 100000)
    {
        return "Clock not synced.";
    }

    // Convert the time_t to a tm struct
    // if (!gmtime_r(&timeToFormat, &timeinfo)) // Use gmtime_r for thread safety
    // {
    //     return "Time unavailable.";
    // }

    // Convert the time_t to a tm struct for local time
    if (!localtime_r(&timeToFormat, &timeinfo)) // Use localtime_r for thread safety
    {
        return "Time unavailable.";
    }

    char buffer[64];
    strftime(buffer, sizeof(buffer), format, &timeinfo);
    return String(buffer); // Convert to Arduino String
}

void TimeHandler::logAllDateTimeFormats()
{
    // Full Date-Time (12-hour format with AM/PM)
    debugI("Full Date-Time (12-hour): %s", formatDateTime("%Y-%m-%d %I:%M:%S %p"));

    // Full Date-Time (24-hour format)
    debugI("Full Date-Time (24-hour): %s", formatDateTime("%Y-%m-%d %H:%M:%S"));

    // Date Only
    debugI("Date Only: %s", formatDateTime("%Y-%m-%d"));

    // Time Only (12-hour format with AM/PM)
    debugI("Time Only (12-hour): %s", formatDateTime("%I:%M:%S %p"));

    // Time Only (24-hour format)
    debugI("Time Only (24-hour): %s", formatDateTime("%H:%M:%S"));

    // Day of the Week
    debugI("Day of the Week: %s", formatDateTime("%A"));

    // Month and Year
    debugI("Month and Year: %s", formatDateTime("%B %Y"));

    // Weekday, Month, and Date
    debugI("Weekday, Month, Date: %s", formatDateTime("%A, %B %d"));

    // Short Date-Time (MM/DD/YY HH:MM)
    debugI("Short Date-Time: %s", formatDateTime("%m/%d/%y %H:%M"));

    // ISO 8601 Format
    debugI("ISO 8601 Format: %s", formatDateTime("%Y-%m-%dT%H:%M:%S"));

    // Linux Epoch Time
    debugI("Linux Epoch Time: %ld", time(nullptr));

    // Custom Timezone String
    debugI("Custom Timezone: %s", formatDateTime("%Z"));
}

#endif // ENABLE_TIME_HANDLER