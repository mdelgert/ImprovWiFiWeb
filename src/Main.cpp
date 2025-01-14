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
#include "OTAHandler.h"
#include "TimeHandler.h"

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
  TimeHandler::init();
  OTAHandler::init();
  //GfxHandler::printMessage(SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(100);
  LedHandler::setColorByName("Purple");
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
  TimeHandler::loop();
  OTAHandler::loop();
}