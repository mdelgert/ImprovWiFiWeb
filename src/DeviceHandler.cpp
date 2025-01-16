#ifdef ENABLE_DEVICE_HANDLER

#include "DeviceHandler.h"

USBHIDMouse DeviceHandler::mouse;
USBHIDKeyboard DeviceHandler::keyboard;

static NonBlockingTimer mouseTimer(100);
static NonBlockingTimer keyboardTimer(100);

void DeviceHandler::loop(){}

void DeviceHandler::init()
{
    USB.begin();
    mouse.begin();
    keyboard.begin();
    registerCommands();
    debugI("DeviceHandler initialized");
}

void DeviceHandler::sendMouseMovement(int x, int y)
{
    // Move the mouse by the specified x and y values
    mouse.move(x, y);
    debugI("Mouse moved: x=%d, y=%d", x, y);
}

void DeviceHandler::sendKeys1(const String& text)
{
    // Type the provided string
    for (size_t i = 0; i < text.length(); i++)
    {
        keyboard.write(text[i]);
        delay(20); // Delay between each key press
    }
    keyboard.write('\n'); // Optional newline
    debugI("Keys sent: %s", text.c_str());
}

void DeviceHandler::sendKeys2(const String& text)
{
    // Type the provided string
    for (size_t i = 0; i < text.length(); i++)
    {
        keyboard.print(text[i]);
    }
    keyboard.write('\n'); // Optional newline
    debugI("Keys sent: %s", text.c_str());
}

void DeviceHandler::sendKeys3(const String& text)
{
    // Type the provided string
    for (size_t i = 0; i < text.length(); i++)
    {
        keyboard.write(text[i]);
    }
    keyboard.write('\n'); // Optional newline
    debugI("Keys sent: %s", text.c_str());
}

void DeviceHandler::registerCommands()
{
    CommandHandler::registerCommand("HID", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (cmd == "mouse") {
           sendMouseMovement(100, 100);
        } else if (cmd == "keys1") {
            sendKeys1(args);
        } else if (cmd == "keys2") {
            sendKeys2(args);
        }
        else if (cmd == "keys3") {
            sendKeys3(args);
        } 
        else {
            debugW("Unknown HID subcommand: %s", cmd.c_str());
        } }, "Handles HID commands. Usage: HID <subcommand> [args]\n"
                                         "  Subcommands:\n"
                                         "  mouse <mouse> - Send x and y\n"
                                         "  keys <keys> - Send keys"
                                         );
}

#endif // ENABLE_DEVICE_HANDLER