Hello I would like to implement keyboard mouse handler in my esp32-s3 micro controller.

Please assume the code base already has wifi connectivity.

All of my code uses the following pattern. Can you provide example following same pattern as below?

#pragma once

#ifdef ENABLE_TEMPLATE_HANDLER

#include "Globals.h"

class TemplateHandler
{
private:
    static void examplePrivate();

public:
    static void init();
    static void loop();
    static void examplePublic();
};

#else

class TemplateHandler { 
public: // No-op implementation of TemplateHandler
    static void init() {} // No-op
    static void loop() {} // No-op
    static void examplePublic() {} // No-op;
};

#endif // ENABLE_TEMPLATE_HANDLER

#ifdef ENABLE_TEMPLATE_HANDLER

#include "TemplateHandler.h"

static NonBlockingTimer myTimer(1000);

void TemplateHandler::init()
{
    debugI("TemplateHandler initialized");
}

void TemplateHandler::loop()
{
    if (myTimer.isReady())
    {
        debugI("TemplateHandler loop");
    }
}

void TemplateHandler::examplePublic()
{
    // Example of debug levels
    debugV("* This is a message of debug level VERBOSE");
    debugD("* This is a message of debug level DEBUG");
    debugI("* This is a message of debug level INFO");
    debugW("* This is a message of debug level WARNING");
    debugE("* This is a message of debug level ERROR");
}

void TemplateHandler::examplePrivate()
{
    debugI("TemplateHandler examplePrivate");
}

#endif // ENABLE_TEMPLATE_HANDLER