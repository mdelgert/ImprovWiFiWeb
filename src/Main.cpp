#include "MainIncludes.h"

void setup()
{
  RemoteDebugHandler::init();
  ConfigManager::init();
  PreferencesHandler::init("settings");
  GfxHandler::init();
  WifiHandler::init();
  WebHandler::init();
  ImprovHandler::init();
  LedHandler::init();
  ButtonHandler::init();
  GfxHandler::printMessage("Ver:" SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(50);
  LedHandler::setColor(CRGB::DarkOrchid);
}

void loop()
{
  RemoteDebugHandler::loop();
  WifiHandler::loop();
  WebHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
}