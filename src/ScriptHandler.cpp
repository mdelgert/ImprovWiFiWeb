#ifdef ENABLE_SCRIPT_HANDLER

#include "ScriptHandler.h"

void ScriptHandler::loop(){}

void ScriptHandler::init()
{
    if (!LittleFS.begin()) {
        debugE("* LittleFS initialization failed!");
        return;
    }

    registerCommands();
    debugI("ScriptHandler initialized.");
}

void ScriptHandler::handleScriptFile(const String &args)
{
    if (args.isEmpty()) {
        debugW("SCRIPT FILE requires a file path. Usage: SCRIPT FILE <path>");
        return;
    }

    if (!LittleFS.exists(args)) {
        debugW("Script file not found: %s", args.c_str());
        return;
    }

    File scriptFile = LittleFS.open(args, "r");
    if (!scriptFile) {
        debugE("Failed to open script file: %s", args.c_str());
        return;
    }

    debugI("Executing script file: %s", args.c_str());

    while (scriptFile.available()) {
        String line = scriptFile.readStringUntil('\n');
        line.trim(); // Remove any leading/trailing whitespace or newlines
        if (!line.isEmpty() && !line.startsWith("REM")) { // Skip empty lines and comments
            debugD("Executing line: %s", line.c_str());
            CommandHandler::handleCommand(line);
        }
    }

    scriptFile.close();
    debugI("Finished executing script file: %s", args.c_str());
}

void ScriptHandler::registerCommands()
{
    CommandHandler::registerCommand("SCRIPT", [](const String &command) {
        String subCommand, args;
        CommandHandler::parseCommand(command, subCommand, args);

        if (CommandHandler::equalsIgnoreCase(subCommand, "FILE")) {
            handleScriptFile(args);
        } else {
            debugW("Unknown SCRIPT subcommand: %s", subCommand.c_str());
        }
    },
    "Handles SCRIPT commands. Usage: SCRIPT <subcommand> [args]\n"
    "  Subcommands:\n"
    "  file <path> - Executes commands from the specified script file.");
}
#endif // ENABLE_SCRIPT_HANDLER
