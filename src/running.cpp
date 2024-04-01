#include <Arduino.h>
#include "simpleTask.h"

void _TaskRunInit()
{
    for (int a = 0; a < TASK_PRIORTY; a++)
    {
        for (int b = 0; b < TASK_MAX; b++)
        {
            // skip if task not used or not runing
            if (!Task[b].GetRunning())
            {
                continue;
            }

            // coperate priority and enable after
            if (Task[b].GetPriority() == a)
            {
                Task[b].RunInit();
            }
        }
    }
}

//apa ini ya kok double
void _TaskRunInit2()
{
    for (int a = 0; a < TASK_PRIORTY; a++)
    {
        for (int b = 0; b < TASK_MAX; b++)
        {
            // skip if task not used or not runing
            if (!Task[b].GetRunning())
            {
                continue;
            }

            // coperate priority and enable after
            if (Task[b].GetPriority() == a)
            {
                Task[b].RunInit();
            }
        }
    }
}

void _taskRunAfterEn(String name)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (Task[a].GetRunning())
        {
            if (name == Task[a].GetRunAfter() && !Task[a].GetRunAfter().isEmpty() && !Task[a].GetEnable())
            {
                Task[a].setEnable();
            }
        }
    }
}

void _TaskRunning()
{

    for (int a = 0; a < TASK_PRIORTY; a++)
    {
        for (int b = 0; b < TASK_MAX; b++)
        {
            // skip if task not used or not runing
            if (!Task[b].GetRunning())
            {
                continue;
            }

            // coperate priority and enable after
            if (Task[b].GetPriority() == a)
            {
                Task[b].run();
                if (Task[b].idle())
                {
                    _taskRunAfterEn(Task[b].GetName());
                }
            }
        }
    }
}

// task Arudino
#ifdef TASK_MOD
void setup()
{
    _SimpleTask();
    _TaskRunInit();
}
void loop()
{
    _TaskRunning();
}
#endif