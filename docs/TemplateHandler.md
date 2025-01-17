I would like to implement ScriptHandler using library LittleFS, that will register a command called SCRIPT.

The subcommand will be called FILE

Please assume the code base already has wifi connectivity.

All of my code uses the following pattern. Can you provide example following same pattern as below?

//TemplateHandler.h

#pragma once

#ifdef ENABLE_TEMPLATE_HANDLER

#include "Globals.h"

class TemplateHandler
{
private:
    static void debugLevels();
    static void registerCommands();

public:
    static void init();
    static void loop();
};

#else

class TemplateHandler { 
public: // No-op implementation of TemplateHandler
    static void init() {} // No-op
    static void loop() {} // No-op
};

#endif // ENABLE_TEMPLATE_HANDLER

//TemplateHandler.cpp

#ifdef ENABLE_TEMPLATE_HANDLER

#include "TemplateHandler.h"

static NonBlockingTimer myTimer(60000);

void TemplateHandler::init()
{
    registerCommands();
    debugI("TemplateHandler initialized");
}

void TemplateHandler::loop()
{
    if (myTimer.isReady())
    {
        debugI("TemplateHandler loop timer.");
    }
}

void TemplateHandler::debugLevels()
{
    // Example of debug levels
    debugV("* This is a message of debug level VERBOSE");
    debugD("* This is a message of debug level DEBUG");
    debugI("* This is a message of debug level INFO");
    debugW("* This is a message of debug level WARNING");
    debugE("* This is a message of debug level ERROR");
}

void TemplateHandler::registerCommands()
{
    CommandHandler::registerCommand("TEMPLATE", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (cmd == "debug") {
            debugLevels();
        } else if (cmd == "hello") {
            debugI("Hello World!");
        } else {
            debugW("Unknown TEMPLATE subcommand: %s", cmd.c_str());
        } }, "Handles TEMPLATE commands. Usage: TEMPLATE <subcommand> [args]\n"
                                         "  Subcommands:\n"
                                         "  debug - Prints debug levels\n"
                                         "  hello - Prints 'Hello World!'");
}

#endif // ENABLE_TEMPLATE_HANDLER
