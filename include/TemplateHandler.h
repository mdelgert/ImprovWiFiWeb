#ifndef TEMPLATE_HANDLER_H
#define TEMPLATE_HANDLER_H

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

#endif
