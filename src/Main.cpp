#include "Globals.h"
#include "TemplateHandler.h"
#include "RemoteDebugHandler.h"
#include "ImprovHandler.h"
#include "GfxHandler.h"
#include "LedHandler.h"
#include "ButtonHandler.h"
#include "WifiHandler.h"
#include "WebHandler.h"
#include "BluetoothHandler.h"
#include "MqttHandler.h"

void setup()
{
  RemoteDebugHandler::init();
  ConfigManager::init();
  TemplateHandler::init();
  BluetoothHandler::init();
  GfxHandler::init();
  WifiHandler::init();
  WebHandler::init();
  ImprovHandler::init();
  LedHandler::init();
  ButtonHandler::init();
  MqttHandler::init();
  GfxHandler::printMessage(SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(0);
  LedHandler::setColorByName("Black");
}

void loop()
{
  RemoteDebugHandler::loop();
  BluetoothHandler::loop();
  TemplateHandler::loop();
  WifiHandler::loop();
  WebHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
  MqttHandler::loop();
}