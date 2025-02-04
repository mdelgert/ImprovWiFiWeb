#ifdef ENABLE_DUCKYSCRIPT_HANDLER

#include "DuckyScriptHandler.h"
#include "DeviceHandler.h"
#include "Globals.h"
#include "LittleFS.h"
#include "KeyMappings.h"

void DuckyScriptHandler::init()
{
    registerCommands();
    debugI("DuckyScriptHandler initialized");
}

void DuckyScriptHandler::executeScript(const String &filePath)
{
    File file = LittleFS.open(filePath, "r");
    if (!file)
    {
        debugE("Failed to open DuckyScript file: %s", filePath.c_str());
        return;
    }

    debugI("Executing DuckyScript from: %s", filePath.c_str());

    while (file.available())
    {
        String line = file.readStringUntil('\n');
        line.trim();
        if (!line.isEmpty() && !line.startsWith("//")) // Ignore empty lines and comments
        {
            processLine(line);
        }
    }

    file.close();
    debugI("DuckyScript execution completed");
}

void DuckyScriptHandler::processLine(const String &line)
{
    String cmd, args;
    CommandHandler::parseCommand(line, cmd, args);

    if (CommandHandler::equalsIgnoreCase(cmd, "DELAY"))
    {
        delay(args.toInt());
    }
    else if (CommandHandler::equalsIgnoreCase(cmd, "STRING"))
    {
        DeviceHandler::sendKeys1(args);
    }
    else
    {
        uint8_t keyCode = getKeyCode(cmd.c_str());
        if (keyCode != 0)
        {
            DeviceHandler::processKey(cmd, true); //press key
            //DeviceHandler::processKey(cmd, false); //release key
            return;
        }

        uint8_t mouseCode = getMouseButtonCode(cmd.c_str());
        if (mouseCode != 0)
        {
            DeviceHandler::sendMouseMovement(mouseCode, 0); // Example for handling mouse button clicks
            return;
        }

        debugW("Unknown DuckyScript command: %s", line.c_str());
    }
}

void DuckyScriptHandler::registerCommands()
{
    CommandHandler::registerCommand("DUCKY", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (CommandHandler::equalsIgnoreCase(cmd, "FILE")) {
            if (args.isEmpty()) {
                debugE("Missing file path for DUCKY FILE command.");
                return;
            }
            executeScript(args);
        } 
        else {
            debugW("Unknown DUCKY subcommand: %s", cmd.c_str());
        } }, "Usage: DUCKY FILE <file_path>");
}

#endif // ENABLE_DUCKYSCRIPT_HANDLER
