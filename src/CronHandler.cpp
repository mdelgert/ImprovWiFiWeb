#ifdef ENABLE_CRON_HANDLER

#include "CronHandler.h"

std::vector<CronHandler::CronJob> CronHandler::cronJobs;

static NonBlockingTimer timeTimer(1000);

void CronHandler::init()
{
    registerCommands();
    debugI("CronHandler initialized");
}

void CronHandler::loop()
{
    if (timeTimer.isReady())
    {
        time_t now = time(nullptr);

        for (auto &job : cronJobs)
        {
            if (now >= job.nextExecution)
            {
                debugI("Executing cron job: %s -> %s", job.schedule.c_str(), job.command.c_str());
                CommandHandler::handleCommand(job.command.c_str());
                updateNextExecution(job);
            }
        }
    }
}

void CronHandler::updateNextExecution(CronJob &job)
{
    time_t now = time(nullptr);
    job.nextExecution = cron_next(&job.expr, now);
    if (job.nextExecution == (time_t)-1)
    {
        debugE("Failed to calculate next execution time for schedule: %s", job.schedule.c_str());
    }
}

void CronHandler::registerCommands() {
    CommandHandler::registerCommand("cron", [](const String &command) {
        debugI("Full Command Received: %s", command.c_str());

        // Locate the first and second quotes for the schedule
        int firstQuoteStart = command.indexOf('\"');
        int firstQuoteEnd = command.indexOf('\"', firstQuoteStart + 1);
        debugI("First Quote Start: %d, First Quote End: %d", firstQuoteStart, firstQuoteEnd);

        if (firstQuoteStart == -1 || firstQuoteEnd == -1) {
            debugE("Invalid syntax. Schedule must be enclosed in double quotes.");
            return;
        }

        // Extract the schedule (first quoted string)
        String schedule = command.substring(firstQuoteStart + 1, firstQuoteEnd);
        schedule.trim(); // Trim the extracted schedule
        debugI("Parsed Schedule: %s", schedule.c_str());

        // Extract everything after the first quoted string
        String remaining = command.substring(firstQuoteEnd + 1);
        remaining.trim();

        // Locate the second set of quotes (if present)
        int secondQuoteStart = remaining.indexOf('\"');
        int secondQuoteEnd = remaining.indexOf('\"', secondQuoteStart + 1);

        String cronCommand;
        if (secondQuoteStart != -1 && secondQuoteEnd != -1) {
            // Extract the actual command after the second set of quotes
            cronCommand = remaining.substring(secondQuoteEnd + 1);
            cronCommand.trim();
        } else {
            // Assume the remaining string is the command
            cronCommand = remaining;
        }

        debugI("Parsed Command: %s", cronCommand.c_str());

        // Validate that both schedule and command are non-empty
        if (schedule.isEmpty()) {
            debugE("Schedule is empty.");
        }
        if (cronCommand.isEmpty()) {
            debugE("Command is empty.");
        }
        if (schedule.isEmpty() || cronCommand.isEmpty()) {
            debugE("Invalid syntax. Both schedule and command must be provided.");
            return;
        }

        // Validate the cron schedule
        cron_expr expr;
        const char *error = nullptr;
        cron_parse_expr(schedule.c_str(), &expr, &error);
        if (error) {
            debugE("Invalid cron schedule: %s. Expected 6 fields (e.g., '* * * * * *').", error);
            return;
        }

        // Calculate the next execution time
        time_t now = time(nullptr);
        time_t nextExecution = cron_next(&expr, now);
        if (nextExecution == (time_t)-1) {
            debugE("Failed to calculate the next execution time for schedule: %s", schedule.c_str());
            return;
        }

        // Register the cron job
        CronJob job = {schedule.c_str(), cronCommand.c_str(), expr, nextExecution};
        cronJobs.push_back(job);

        debugI("Cron job registered: %s -> %s", schedule.c_str(), cronCommand.c_str());
    }, "Handles cron jobs. Usage: cron register \"<schedule>\" <command>");
}

#endif // ENABLE_CRON_HANDLER
