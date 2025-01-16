#pragma once

#ifdef ENABLE_DEVICE_HANDLER

#include "Globals.h"
#include "DeviceDescriptors.h" //Change usb string descriptors
#include <USB.h>
#include <USBHIDMouse.h>
#include <USBHIDKeyboard.h>

class DeviceHandler
{
private:
    static USBHIDMouse mouse;
    static USBHIDKeyboard keyboard;
    static void sendMouseMovement(int x, int y);
    static void registerCommands();
    static void sendKeys1(const String& text);
    static void sendKeys2(const String& text);
    static void sendKeys3(const String& text);

public:
    static void loop();
    static void init();
};

#else

class DeviceHandler
{
public: // No-op implementation of DeviceHandler
    static void loop() {} // No-op
    static void init() {} // No-op
};

#endif // ENABLE_DEVICE_HANDLER