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
#include "EzTimeHandler.h"

void setup()
{
  TemplateHandler::init();
  RemoteDebugHandler::init();
  ConfigManager::init();
  BluetoothHandler::init();
  GfxHandler::init();
  WifiHandler::init();
  WebHandler::init();
  ImprovHandler::init();
  LedHandler::init();
  ButtonHandler::init();
  MqttHandler::init();
  EzTimeHandler::init();
  GfxHandler::printMessage(SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(0);
  LedHandler::setColorByName("Black");
}

void loop()
{
  TemplateHandler::loop();
  RemoteDebugHandler::loop();
  BluetoothHandler::loop();
  WifiHandler::loop();
  WebHandler::loop();
  ImprovHandler::loop();
  ButtonHandler::loop();
  MqttHandler::loop();
  EzTimeHandler::loop();
}