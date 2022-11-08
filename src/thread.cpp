#include <Arduino.h>
#include "simpleTask.h"

void thread::NewTask(int delay)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].getRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        Task[this->idleID].priority = 5;
        Task[this->idleID].id = this->idleID;
        Task[this->idleID].SetTask();
        Task[this->idleID].setTimeMS(delay);
    }
}
void thread::NewTask(int delay, uint8_t priority)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].getRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        if (priority > 5)
            priority = 5;
        Task[this->idleID].priority = priority;
        Task[this->idleID].id = this->idleID;
        Task[this->idleID].SetTask();
        Task[this->idleID].setTimeMS(delay);
    }
}
void thread::NewTask(int delay, uint8_t priority, bool us)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].getRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        if (priority > 5)
            priority = 5;
        Task[this->idleID].priority = priority;
        Task[this->idleID].id = this->idleID;
        Task[this->idleID].SetTask();
        if (us)
            Task[this->idleID].setTime(delay);
        else
            Task[this->idleID].setTimeMS(delay);
    }
}
void thread::Exc(task::HandlerFunc fn)
{
    Task[this->idleID].Exc(fn);
}
void thread::Exc(task::HandlerFunc2 fn)
{
    Task[this->idleID].Exc(fn);
}
void thread::Mode(uint8_t mode)
{
    Task[this->idleID].mode = mode;
}
void thread::Mode(uint8_t mode, String after)
{
    Task[this->idleID].setDisable();
    Task[this->idleID].mode = mode;
    Task[this->idleID].runAfter = after;
}
void thread::TaskName(String name)
{
    Task[this->idleID].name = name;
}

void _taskRunAfterEn(String name)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (Task[a].getRunning())
        {
            if (name == Task[a].runAfter && !Task[a].runAfter.isEmpty())
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
            if (!Task[b].getRunning())
            {
                continue;
            }

            // coperate priority and enable after
            if (Task[b].priority == a)
            {
                Task[b].run();
                if (Task[b].idle())
                {
                    _taskRunAfterEn(Task[b].name);
                }
            }
        }
    }
}
