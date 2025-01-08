#include "Globals.h"
#include <Arduino.h>
#include "NonBlockingTimer.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "PreferencesHandler.h"
#include "GfxHandler.h"
#include "LEDHandler.h"
#include "ButtonHandler.h"
#include "WifiHandler.h"
#include "WebHandler.h"

void setup()
{
  RemoteDebugHandler::init();
  PreferencesHandler::init("settings");
  GfxHandler::init();
  WifiHandler::init();
  WebHandler::init();
  ImprovHandler::init();
  LEDHandler::init();
  ButtonHandler::init();
  //GfxHandler::printMessage("Ver:" SOFTWARE_VERSION);
  LEDHandler::setDefaultBrightness(50);
  LEDHandler::setColor(CRGB::Purple);
}

void loop()
{
  RemoteDebugHandler::loop();
  WifiHandler::loop();
  WebHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
}