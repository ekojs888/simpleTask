#include <Arduino.h>
#include "simpleTask.h"
#include <simpleLog.h>

void tes2(task *Arg);

int no = 0;
void tes1(task *Arg)
{
    pinMode(2, OUTPUT);
    Log.Print("test firstn\n");
    Arg->Loop(tes2, 500 * TASK_DELAY_MS);
}
void tes2(task *Arg)
{
    if (no >= 10)
    {
        digitalWrite(2, Arg->getToggle());
        Log.Print("delay loop\n");
    }
    else
    {
        Log.Print("%d\n",no);
        no++;
    }
}
void tes4(task *Arg)
{
    Log.Print("delay loop3\n");
}
void tes3(task *Arg)
{
    digitalWrite(2, Arg->getToggle());
    Log.Print("delay loop 3\n");
    Arg->Loop(tes4, 1000 * TASK_DELAY_MS);
}

void _SimpleTask()
{
    Log.init(9600);
    thread t1;
    t1.NewTask(TASK_PRIORTY_5, "Init", tes1);
    t1.NewTask(TASK_PRIORTY_0, "Init2", tes3);
}
