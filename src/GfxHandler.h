#pragma once

#ifdef ENABLE_GFX_HANDLER

#include "Globals.h"
#include <LovyanGFX.hpp>
#include "GfxLockImage.h"
#include "TimeHandler.h"

// Define the display configuration for LILYGO T-Dongle-S3
class LGFX_LiLyGo_TDongleS3 : public lgfx::LGFX_Device {
    lgfx::Panel_ST7735S _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX_LiLyGo_TDongleS3();
};

// Define the handler for LovyanGFX
class GfxHandler {
private:
    static NonBlockingTimer clockTimer;
    static bool showClock;
    static void toggleClock(bool state);
    static LGFX_LiLyGo_TDongleS3 tft;
    static void registerCommands();

public:
    static void init();
    static void loop();
    static void printMessage(const String &message);
    static void drawImage(int x, int y, int width, int height, const char *data);
};

#else
class GfxHandler {
public:
    static void init() {}
    static void loop() {}
    static void printMessage(const String &message) {} // Consistent parameter type
    static void drawImage(int, int, int, int, const char *) {}
};
#endif // ENABLE_GFX_HANDLER