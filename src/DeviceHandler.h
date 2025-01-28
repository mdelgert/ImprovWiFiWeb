#pragma once

#ifdef ENABLE_DEVICE_HANDLER

#include <USBHIDMouse.h>
#include <USBHIDKeyboard.h>

class DeviceHandler
{
private:
    static USBHIDMouse mouse;
    static USBHIDKeyboard keyboard;
    static void sendKeys1(const String& text);
    static void sendKeys2(const String& text);
    static void tapKey(const String& key);
    static void processKey(const String& keyName, bool press);
    static void registerCommands();
    
public:
    static void sendMouseMovement(int x, int y);
    static USBHIDKeyboard& getKeyboard();
    static int keyPressDelay; // Configurable delay for key presses
    static void setKeyPressDelay(int delay);
    static void loop();
    static void init();
};

#else
class USBHIDKeyboard;
class DeviceHandler
{
public: // No-op implementation of DeviceHandler
    static void sendMouseMovement(int x, int y) {} // No-op
    static USBHIDKeyboard fakeKeyboard;
    static int keyPressDelay;
    static void loop() {} // No-op
    static void init() {} // No-op
};

#endif // ENABLE_DEVICE_HANDLER