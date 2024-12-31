#include <Arduino.h>
#include "Globals.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "PreferencesHandler.h"
#include "NonBlockingTimer.h"
#include "GfxHandler.h"
#include "LEDHandler.h"

NonBlockingTimer myTimer(1000);

void setup()
{
  //Serial.begin(115200);
  RemoteDebugHandler::init();
  PreferencesHandler::init("settings");
  GfxHandler::init();
  ImprovHandler::init();
  LEDHandler::init();
  // GfxHandler::printMessage("Ver:" SOFTWARE_VERSION);
  LEDHandler::setColor(CRGB::Green);
}

void loop()
{
  RemoteDebugHandler::loop();
  ImprovHandler::loop();

  // THIS IS INTERFERING WITH IMPROVE IN SETUP MODE - NEED TO FIX !!!!!!!!!!!!!!!!!!
  // if (myTimer.isReady())
  // {
  //   debugI("Ver:" SOFTWARE_VERSION);
  // }
}