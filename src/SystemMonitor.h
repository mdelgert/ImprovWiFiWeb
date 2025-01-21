//SystemMonitor.h

#pragma once

#ifdef ENABLE_SYSTEM_MONITOR

#include "Globals.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class SystemMonitor {
private:
    static void systemMonitorTask(void *parameter);

public:
    static void init();
};

#else

class SystemMonitor { 
public:
    static void init() {} // No-op
};

#endif // ENABLE_SYSTEM_MONITOR