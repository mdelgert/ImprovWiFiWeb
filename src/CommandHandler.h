#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "Globals.h"
#include <Arduino.h>
#include <map>
#include <functional>

class CommandHandler {
public:
    static void handleCommand(const String& command);
    static void registerCommand(const String& name, std::function<void(const String&)> handler, const String& description = "");
    static void registerCommandAlias(const String& alias, const String& existingCommand);
    static void listCommands();
    static void setDefaultHandler(std::function<void(const String&)> handler);

private:
    static std::map<String, std::function<void(const String&)>> commandRegistry;
    static std::map<String, String> commandDescriptions;
    static std::function<void(const String&)> defaultHandler;

    static void parseCommand(const String& input, String& cmd, String& args);
};

#endif // COMMAND_HANDLER_H
