#pragma once

#ifdef ENABLE_SCRIPT_HANDLER

#include "Globals.h"
#include <LittleFS.h>

class ScriptHandler
{
private:
    static void handleScriptFile(const String &args);
    static void registerCommands();

public:
    static void loop();
    static void init();
};

#else

class ScriptHandler {
public: // No-op implementation of ScriptHandler
    static void loop() {}
    static void init() {}
};

#endif // ENABLE_SCRIPT_HANDLER
