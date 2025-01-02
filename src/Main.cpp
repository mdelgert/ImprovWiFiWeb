#include <Arduino.h>
#include "Globals.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "PreferencesHandler.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"
#include "LEDHandler.h"
#include "ButtonHandler.h"

NonBlockingTimer myTimer(1000);

void setup()
{
  RemoteDebugHandler::init();
  PreferencesHandler::init("settings");
  GfxHandler::init();
  ImprovHandler::init();
  LEDHandler::init();
  ButtonHandler::init();
  GfxHandler::printMessage("Ver:" SOFTWARE_VERSION);
  LEDHandler::setDefaultBrightness(255);
  LEDHandler::setColor(CRGB::Maroon);
}

void loop()
{
  RemoteDebugHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();

  // THIS IS INTERFERING WITH IMPROVE IN SETUP MODE - NEED TO FIX !!!!!!!!!!!!!!!!!!
  // if (myTimer.isReady())
  // {
  //   debugI("Ver:" SOFTWARE_VERSION);
  // }
}