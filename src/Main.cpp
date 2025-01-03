#include <Arduino.h>
#include "Globals.h"
#include "NonBlockingTimer.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "PreferencesHandler.h"
#include "GfxHandler.h"
#include "LEDHandler.h"
#include "ButtonHandler.h"
#include "TemplateHandler.h"

NonBlockingTimer myTimer(5000);

void setup()
{
  RemoteDebugHandler::init();
  PreferencesHandler::init("settings");
  TemplateHandler::init();
  GfxHandler::init();
  ImprovHandler::init();
  LEDHandler::init();
  ButtonHandler::init();
  GfxHandler::printMessage("Ver:" SOFTWARE_VERSION);
  LEDHandler::setDefaultBrightness(100);
  LEDHandler::setColor(CRGB::DarkBlue);
}

void loop()
{
  RemoteDebugHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
  TemplateHandler::loop();

  if (myTimer.isReady())
  {
    debugI("Timer is ready");
  }
}