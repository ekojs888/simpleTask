#include <Arduino.h>
#include "simpleTask.h"

thread *thread::NewTask(int delay)
{
    this->priority = 5;
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[this->priority][a].getRunning())
        {
            this->idleID = a;
            break;
        }
    }
    Task[this->priority][this->idleID].id = this->idleID;
    Task[this->priority][this->idleID].SetTask();
    Task[this->priority][this->idleID].setTimeMS(delay);
    return this;
}
thread *thread::NewTask(int delay, uint8_t priority)
{
    this->priority = priority;
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[priority][a].getRunning())
        {
            this->idleID = a;
            break;
        }
    }
    Task[this->priority][this->idleID].SetTask();
    Task[this->priority][this->idleID].setTimeMS(delay);
    return this;
}
// thread *thread::NewTaskC(int delay)
// {
//     this->idleID = -1;
//     for (int a = 0; a < TASK_MAX; a++)
//     {
//         if (!Task[a].getRunning())
//         {
//             this->idleID = a;
//             break;
//         }
//     }
//     Task[this->idleID].SetTask();
//     Task[this->idleID].setTime(delay);
//     return this;
// }
// bool thread::Idle()
// {
//     return Task[this->idleID].idle();
// }

// bool thread::IdleToggle()
// {
//     return Task[this->idleID].getToggle();
// }

// void thread::StopTask()
// {
//     Task[this->idleID].KillTask();
// }

// void thread::Enable()
// {
//     Task[this->idleID].setEnable();
// }
// void thread::Disable()
// {
//     Task[this->idleID].setDisable();
// }
void thread::Exc(task::HandlerFunc fn)
{
    Task[this->priority][this->idleID].Exc(fn);
}
void thread::Mode(uint8_t mode)
{
    Task[this->priority][this->idleID].mode = mode;
}
void thread::Mode(uint8_t mode, String after)
{
    Task[this->priority][this->idleID].setDisable();
    Task[this->priority][this->idleID].mode = mode;
    Task[this->priority][this->idleID].runAfter = after;
}
void thread::TaskName(String name)
{
    Task[this->priority][this->idleID].name = name;
}

void _taskRunAfterEn(String name)
{
    for (int b = 0; b < TASK_PRIORTY; b++)
    {
        for (int a = 0; a < TASK_MAX; a++)
        {
            if (Task[b][a].getRunning())
            {
                if (name == Task[b][a].runAfter && !name.isEmpty())
                {
                    Task[b][a].setEnable();
                }
            }
        }
    }
}
void _TaskRunning()
{
    for (int b = 0; b < TASK_PRIORTY; b++)
    {
        for (int a = 0; a < TASK_MAX; a++)
        {
            if (Task[b][a].getRunning())
            {
                Task[b][a].run();
                _taskRunAfterEn(Task[b][a].name);
            }
        }
    }
}
