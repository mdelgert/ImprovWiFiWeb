#include "CommandHandler.h"

std::map<String, std::function<void(const String&)>> CommandHandler::commandRegistry;

void CommandHandler::handleCommand(const String& command) {
    String cmd = command;
    String args = "";

    int spaceIndex = command.indexOf(' ');
    if (spaceIndex > 0) {
        cmd = command.substring(0, spaceIndex);
        args = command.substring(spaceIndex + 1);
    }

    if (commandRegistry.find(cmd) != commandRegistry.end()) {
        commandRegistry[cmd](args); // Call the registered handler
    } else {
        Serial.println("Unknown command: " + cmd);
    }
}

void CommandHandler::registerCommand(const String& name, std::function<void(const String&)> handler) {
    commandRegistry[name] = handler;
}

/* Usage example:

#include "CommandHandler.h"

void setup()
{
    CommandHandler::registerCommand("test", runCommand);
}

void runCommand(const String &command) {
    String cmd = command;
    String args = "";

    int spaceIndex = command.indexOf(' ');
    if (spaceIndex > 0) {
        cmd = command.substring(0, spaceIndex);
        args = command.substring(spaceIndex + 1);
    }

    cmd.toLowerCase();

    if (cmd == "hello") {
        debugI("Hello World!");
    } else {
        debugW("Unknown command: %s", cmd.c_str());
    }
}
*/