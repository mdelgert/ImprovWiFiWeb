#ifdef ENABLE_BUTTON_HANDLER

#include "ButtonHandler.h"
#include "Globals.h"
#include "LedHandler.h"
#include "GfxHandler.h"
#include <OneButton.h>
#include <WiFi.h>
#include <LittleFS.h>

// Define static members
static NonBlockingTimer myTimer(1000);
static OneButton button(BUTTON_PIN, true);

// Initialize the button
void ButtonHandler::init()
{
    button.attachClick(handleSingleClick);
    button.attachDoubleClick(handleDoubleClick);
    button.attachLongPressStart(handleLongPress);
    debugI("ButtonHandler initialized on pin: %d", BUTTON_PIN);
}

// Update the button state (call in loop)
void ButtonHandler::loop()
{
    button.tick();
}

// Button action handlers
void ButtonHandler::handleSingleClick()
{
    debugI("Single click.");
    // GfxHandler::printMessage("Single click.");
    GfxHandler::printMessage(SOFTWARE_VERSION);
    LedHandler::setColorByName("white");
}

void ButtonHandler::handleDoubleClick()
{
    debugI("Double click.");
    // GfxHandler::printMessage("Double click.");
    String ipAddress = WiFi.localIP().toString();
    GfxHandler::printMessage("IP: " + ipAddress);
    LedHandler::setColorByName("green");
}

void ButtonHandler::handleLongPress()
{
    debugI("Erasing device!");
    GfxHandler::printMessage("Erasing device!");
    LedHandler::setColorByName("red");
    ConfigManager::clear();
    
    //Don't use this, it will erase the whole filesystem and can't use webserver to reconfigure
    //Only enable for development testing etc....
    //LittleFS.format();

    if (myTimer.isReady()) // Adding delay was rebooting before clearing preferences
    {
        ESP.restart();
    }
}

#endif // ENABLE_BUTTON_HANDLER