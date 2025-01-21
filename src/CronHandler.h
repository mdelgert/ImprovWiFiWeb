#pragma once

#ifdef ENABLE_CRON_HANDLER

#include "Globals.h"
#include "CommandHandler.h"
#include "NonBlockingTimer.h"
#include <vector>
#include <functional>
#include <string>
#include "CronExpr.h"

class CronHandler {
private:
    struct CronJob {
        std::string schedule;
        std::string command;
        cron_expr expr;
        time_t nextExecution;
    };

    static std::vector<CronJob> cronJobs;
    static void updateNextExecution(CronJob &job);
    static void registerCommands();

public:
    static void init();
    static void loop();
};

#else

class CronHandler {
public:
    static void init() {} // No-op
    static void loop() {} // No-op
};

#endif // ENABLE_CRON_HANDLER
