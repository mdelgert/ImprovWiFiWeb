#ifdef ENABLE_SYSTEM_MONITOR

#include "SystemMonitor.h"

// Timing intervals (in milliseconds)
constexpr unsigned long SECOND_CHECK_INTERVAL = 1000;
constexpr unsigned long MINUTE_CHECK_INTERVAL = 60000;
constexpr unsigned long FIVE_MINUTE_CHECK_INTERVAL = 300000;
constexpr unsigned long TEN_MINUTE_CHECK_INTERVAL = 600000;

// Task handle for the SystemMonitor task
TaskHandle_t systemMonitorTaskHandle = nullptr;

// Function prototypes
void SystemMonitor::init()
{
  // Update boot count and time
  settings.bootCount++;
  settings.bootTime = time(nullptr);
  settings.upTime++;
  ConfigManager::save();

  // Create the SystemMonitor task
  xTaskCreatePinnedToCore(
      systemMonitorTask,        // Task function
      "SystemMonitor",          // Name of the task
      4096,                     // Stack size
      nullptr,                  // Parameter
      1,                        // Priority
      &systemMonitorTaskHandle, // Task handle
      1                         // Core
  );
}

// SystemMonitor task
void SystemMonitor::systemMonitorTask(void *parameter)
{
  unsigned long lastCheckTimes[] = {0, 0, 0, 0}; // Index: 0-Second, 1-Minute, 2-FiveMinute, 3-TenMinute
  constexpr unsigned long intervals[] = {
      SECOND_CHECK_INTERVAL,
      MINUTE_CHECK_INTERVAL,
      FIVE_MINUTE_CHECK_INTERVAL,
      TEN_MINUTE_CHECK_INTERVAL};

  while (true)
  {
    unsigned long currentMillis = millis();

    for (int i = 0; i < 4; i++)
    {
      if (currentMillis - lastCheckTimes[i] >= intervals[i])
      {
        lastCheckTimes[i] = currentMillis;

        // Call the specific handler for each interval
        switch (i)
        {
        case 0:
          handleSecondCheck();
          break;
        case 1:
          handleMinuteCheck();
          break;
        case 2:
          handleFiveMinuteCheck();
          break;
        case 3:
          handleTenMinuteCheck();
          break;
        }
      }
    }

    vTaskDelay(pdMS_TO_TICKS(100)); // Sleep for 100 ms
  }
}

// Define individual handlers for each interval
void handleSecondCheck()
{
  debugI("SystemMonitor: Running second-specific task.");
  // TimeHandler::logAllDateTimeFormats();
  settings.upTime++;
  settings.currentTime = TimeHandler::formatDateTime("%I:%M:%S %p");
  settings.currentDate = TimeHandler::formatDateTime("%m-%d-%Y");
  GfxHandler::printMessage(TimeHandler::formatDateTime("%I:%M:%S %p"));
}

void handleMinuteCheck()
{
  debugI("SystemMonitor: Running minute-specific task.");
}

void handleFiveMinuteCheck()
{
  debugI("SystemMonitor: Running five-minute-specific task.");
}

void handleTenMinuteCheck()
{
  debugI("SystemMonitor: Running ten-minute-specific task.");
}

#endif // ENABLE_SYSTEM_MONITOR
