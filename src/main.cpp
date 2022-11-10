#include <Arduino.h>
#include "simpleTask.h"

void tesInit()
{
    pinMode(2, OUTPUT);
}
void tesRun(task *Arg)
{
    digitalWrite(2, Arg->getToggle());
}

thread t1, t2;

void setup()
{
    auto ts = t1.NewTask(1000, 5);
    ts->SetName("Foo");
    ts->SetMode(TASK_MODE_ONESHOOT);
    ts->Exc(tesInit);

    ts = t2.NewTask(200, 0);
    ts->SetName("Flop");
    ts->SetMode(TASK_MODE_DEFAULT);
    ts->Exc(tesRun);
}

void loop()
{
    _TaskRunning();
}