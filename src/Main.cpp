#include "Globals.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "GfxHandler.h"
#include "LedHandler.h"
#include "ButtonHandler.h"
#include "WifiHandler.h"
#include "WebHandler.h"

void setup()
{
  RemoteDebugHandler::init();
  ConfigManager::init();
  GfxHandler::init();
  WifiHandler::init();
  WebHandler::init();
  ImprovHandler::init();
  LedHandler::init();
  ButtonHandler::init();
  //GfxHandler::printMessage("Firmware:" SOFTWARE_VERSION);
  GfxHandler::printMessage(SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(150);
  LedHandler::setColorByName("White");
}

void loop()
{
  RemoteDebugHandler::loop();
  WifiHandler::loop();
  WebHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
}