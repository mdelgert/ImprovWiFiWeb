#pragma once

#ifdef ENABLE_BUTTON_HANDLER

#include "Globals.h"
#include <OneButton.h>
#include "LedHandler.h"
#include "GfxHandler.h"

// Full implementation of ButtonHandler
class ButtonHandler {
public:
    static void init();
    static void loop();

private:
    static OneButton button;
    static void handleSingleClick();
    static void handleDoubleClick();
    static void handleLongPress();
};

#else
// No-op implementation of ButtonHandler
class ButtonHandler {
public:
    static void init() {} // No-op
    static void loop() {} // No-op
};

#endif // ENABLE_BUTTON_HANDLER
