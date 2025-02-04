#include "Globals.h"
#include "TemplateHandler.h"
#include "RemoteDebugHandler.h"
#include "GfxHandler.h"
#include "LedHandler.h"
#include "ButtonHandler.h"
#include "WebHandler.h"
#include "BluetoothHandler.h"
#include "MqttHandler.h"
#include "OTAHandler.h"
#include "TimeHandler.h"
#include "CommandHandler.h"
#include "DeviceHandler.h"
#include "ScriptHandler.h"
#include "CronHandler.h"
#include "SystemMonitor.h"
#include "DownloadHandler.h"
#include "AesHandler.h"
#include "JiggleHandler.h"
#include "ImprovWiFiHandler.h"
#include "LittleFsHandler.h"

void setup()
{
  RemoteDebugHandler::init();
  LittleFsHandler::init();
  ScriptHandler::init();
  ConfigManager::init();
  BluetoothHandler::init();
  GfxHandler::init();
  ImprovWiFiHandler::init();
  WebHandler::init();
  LedHandler::init();
  ButtonHandler::init();
  MqttHandler::init();
  OTAHandler::init();
  CommandHandler::init();
  DeviceHandler::init();
  CronHandler::init();
  SystemMonitor::init();
  DownloadHandler::init();
  AesHandler::init();
  TimeHandler::init(settings.timezone);
  JiggleHandler::init();
  //GfxHandler::printMessage(SOFTWARE_VERSION);
  LedHandler::setDefaultBrightness(100);
  //LedHandler::setColorByName("purple");
  LedHandler::setColorByName("green");
}

void loop()
{
  RemoteDebugHandler::loop();
  ScriptHandler::loop();
  BluetoothHandler::loop();
  GfxHandler::loop();
  ImprovWiFiHandler::loop();
  WebHandler::loop();
  ButtonHandler::loop();
  MqttHandler::loop();
  OTAHandler::loop();
  DeviceHandler::loop();
  CronHandler::loop();
  JiggleHandler::loop();
}