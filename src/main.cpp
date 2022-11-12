#include <Arduino.h>
#include "simpleTask.h"
#include "log.h"
#include "srv/init.h"

void setup()
{
    RunInit();
}

void loop()
{
    _TaskRunning();
}
