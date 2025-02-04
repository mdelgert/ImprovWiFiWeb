#ifdef ENABLE_DUCKYSCRIPT_HANDLER

#include "DuckyScriptHandler.h"
#include "DeviceHandler.h"
#include "Globals.h"
#include "LittleFS.h"
#include "KeyMappings.h"

static NonBlockingTimer scriptTimer(5000);
static String scriptFilePath = "/default.ducky"; // Default script file

void DuckyScriptHandler::init()
{
    registerCommands();
    debugI("DuckyScriptHandler initialized");
}

void DuckyScriptHandler::loop()
{
    if (scriptTimer.isReady())
    {
        debugI("Executing DuckyScript from: %s", scriptFilePath.c_str());
        executeScript(scriptFilePath);
    }
}

void DuckyScriptHandler::executeScript(const String &filePath)
{
    File file = LittleFS.open(filePath, "r");
    if (!file)
    {
        debugE("Failed to open DuckyScript file: %s", filePath.c_str());
        return;
    }

    while (file.available())
    {
        String line = file.readStringUntil('\n');
        line.trim();
        if (!line.isEmpty() && !line.startsWith("//"))
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
        int delayMs = args.toInt();
        delay(delayMs);
    }
    else if (CommandHandler::equalsIgnoreCase(cmd, "STRING"))
    {
        DeviceHandler::sendKeys1(args);
    }
    else
    {
        // Handle raw keys via KeyMappings
        uint8_t keyCode = getKeyCode(cmd.c_str());
        if (keyCode != 0)
        {
            DeviceHandler::processKey(cmd, true);
            DeviceHandler::processKey(cmd, false);
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

        if (CommandHandler::equalsIgnoreCase(cmd, "RUN")) {
            debugI("Executing DuckyScript from: %s", scriptFilePath.c_str());
            executeScript(scriptFilePath);
        } 
        else if (CommandHandler::equalsIgnoreCase(cmd, "SETFILE")) {
            scriptFilePath = args;
            debugI("DuckyScript file set to: %s", scriptFilePath.c_str());
        } 
        else {
            debugW("Unknown DUCKY subcommand: %s", cmd.c_str());
        } }, "Usage: DUCKY <RUN|SETFILE <file_path>>");
}

#endif // ENABLE_DUCKYSCRIPT_HANDLER
