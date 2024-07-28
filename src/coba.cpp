#include <Arduino.h>
#include "simpleTask.h"

int a =0;

void task2(task *Arg)
{
    if (a < 10)
    {
        digitalWrite(26, Arg->getToggle());
        a++;
    }
}
void task1(task *Arg)
{
    pinMode(26, OUTPUT);
    Arg->Loop(task2, 500 * TASK_DELAY_MS);
}

void _SimpleTask()
{
    thread t1;
    t1.NewTask(TASK_PRIORTY_5, "Init", task1);
}