// JiggleHandler.cpp

#ifdef ENABLE_JIGGLE_HANDLER

#include "JiggleHandler.h"
#include "DeviceHandler.h"

// Define the default interval and amount in one place
constexpr int DEFAULT_JIGGLE_INTERVAL = 60000;
constexpr int DEFAULT_JIGGLE_AMOUNT = 5;

bool JiggleHandler::jiggleEnabled = false;                            // Jiggle initially disabled
NonBlockingTimer JiggleHandler::jiggleTimer(DEFAULT_JIGGLE_INTERVAL); // Use the default interval here
int JiggleHandler::jiggleInterval = DEFAULT_JIGGLE_INTERVAL;          // Use the same default interval here
int JiggleHandler::jiggleAmount = DEFAULT_JIGGLE_AMOUNT;              // Default jiggle amount

void JiggleHandler::init()
{
    registerCommands();
    debugI("JiggleHandler initialized");
}

void JiggleHandler::loop()
{
    if (jiggleEnabled && jiggleTimer.isReady())
    {
        performJiggle();
    }
}

void JiggleHandler::performJiggle()
{
    // Move the mouse slightly in a square pattern based on jiggleAmount
    DeviceHandler::sendMouseMovement(jiggleAmount, -jiggleAmount);
    delay(50);
    DeviceHandler::sendMouseMovement(-jiggleAmount, jiggleAmount);
    delay(50);
    debugI("Mouse jiggled with amount: %d.", jiggleAmount);
}

void JiggleHandler::registerCommands()
{
    CommandHandler::registerCommand("jiggle", [](const String &command)
                                    {
        String cmd, args;
        CommandHandler::parseCommand(command, cmd, args);

        if (CommandHandler::equalsIgnoreCase(cmd, "true"))
        {
            jiggleEnabled = true;
            debugI("Mouse jiggle enabled.");
        }
        else if (CommandHandler::equalsIgnoreCase(cmd, "false"))
        {
            jiggleEnabled = false;
            debugI("Mouse jiggle disabled.");
        }
        else if (CommandHandler::equalsIgnoreCase(cmd, "time"))
        {
            int interval = args.toInt();
            if (interval > 0)
            {
                jiggleInterval = interval;
                jiggleTimer.setInterval(jiggleInterval);
                debugI("Mouse jiggle interval set to %d ms.", jiggleInterval);
            }
            else
            {
                debugW("Invalid interval: %s", args.c_str());
            }
        }
        else if (CommandHandler::equalsIgnoreCase(cmd, "amount"))
        {
            int amount = args.toInt();
            if (amount > 0)
            {
                jiggleAmount = amount;
                debugI("Mouse jiggle amount set to %d.", jiggleAmount);
            }
            else
            {
                debugW("Invalid amount: %s", args.c_str());
            }
        }
        else
        {
            debugW("Unknown jiggle subcommand: %s", cmd.c_str());
        } }, "Handles JIGGLE commands. Usage: JIGGLE <subcommand> [args]\n"
             "  Subcommands:\n"
             "  true - Enables mouse jiggle\n"
             "  false - Disables mouse jiggle\n"
             "  time <ms> - Sets the jiggle interval in milliseconds\n"
             "  amount <pixels> - Sets the jiggle amount in pixels");
}

#endif // ENABLE_JIGGLE_HANDLER