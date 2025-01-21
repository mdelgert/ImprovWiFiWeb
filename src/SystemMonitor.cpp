//SystemMonitor.cpp

#ifdef ENABLE_SYSTEM_MONITOR

#include "SystemMonitor.h"

// Timing intervals (in milliseconds)
constexpr unsigned long secoundCheckInterval = 1000;
constexpr unsigned long minuteCheckInterval = 60000;
constexpr unsigned long fiveMinuteCheckInterval = 300000;
constexpr unsigned long tenMinuteCheckInterval = 600000;

// Task handle for the SystemMonitor task
TaskHandle_t systemMonitorTaskHandle = nullptr;

void SystemMonitor::init() {
  // Create the SystemMonitor task
  xTaskCreatePinnedToCore(
    systemMonitorTask,    // Task function
    "SystemMonitor",      // Name of the task
    4096,                 // Stack size
    nullptr,              // Parameter
    1,                    // Priority
    &systemMonitorTaskHandle, // Task handle
    1                     // Core
  );
}

void SystemMonitor::systemMonitorTask(void *parameter) {
  unsigned long previousSecoundCheck = 0;
  unsigned long previousMinuteCheck = 0;
  unsigned long previousFiveMinuteCheck = 0;
  unsigned long previousTenMinuteMinuteCheck = 0;

  for (;;) {
    unsigned long currentMillis = millis();

    //Secound check
    if (currentMillis - previousSecoundCheck >= secoundCheckInterval) {
      previousSecoundCheck = currentMillis;
      debugI("Secound check!");
    }

    //Minute check
    if (currentMillis - previousMinuteCheck >= minuteCheckInterval) {
      previousMinuteCheck = currentMillis;
      debugI("Minute check!");
    }

    //Five minute check
    if (currentMillis - previousFiveMinuteCheck >= fiveMinuteCheckInterval) {
      previousFiveMinuteCheck = currentMillis;
      debugI("Five minute check!");
    }

    //Ten minute check
    if (currentMillis - previousTenMinuteMinuteCheck >= tenMinuteCheckInterval) {
      previousTenMinuteMinuteCheck = currentMillis;
      debugI("Ten minute check!");
    }

    vTaskDelay(100 / portTICK_PERIOD_MS); // Sleep for 100 ms
  }
}

#endif // ENABLE_SYSTEM_MONITOR