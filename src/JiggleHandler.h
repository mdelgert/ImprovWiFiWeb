// JiggleHandler.h

#pragma once

#ifdef ENABLE_JIGGLE_HANDLER

#include "Globals.h"

class JiggleHandler
{
private:
    static NonBlockingTimer jiggleTimer;
    static bool jiggleEnabled;
    static int jiggleInterval;
    static int jiggleAmount;
    static void registerCommands();
    static void performJiggle();

public:
    static void init();
    static void loop();
};

#else

class JiggleHandler
{
public:
    static void init() {} // No-op
    static void loop() {} // No-op
};

#endif // ENABLE_JIGGLE_HANDLER
