#pragma once

#ifdef ENABLE_DOWNLOAD_HANDLER

#include "Globals.h"
#include <LittleFS.h>
#include <HTTPClient.h>

class DownloadHandler
{
private:
    static void registerCommands();
    static bool downloadFile(const String &url, const String &destinationPath);

public:
    static void init();
};

#else

class DownloadHandler
{
public: // No-op implementation of DownloadHandler
    static void init() {}
};

#endif // ENABLE_DOWNLOAD_HANDLER
