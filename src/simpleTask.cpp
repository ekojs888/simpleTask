#include <Arduino.h>
#include "simpleTask.h"

task Task[TASK_MAX];

void task::KillTask()
{
    this->running = false;
}
void task::SetTask()
{
    this->running = true;
}
void task::setTime(int delay)
{
    this->enable = true;
    this->delay = delay;
}
void task::setTimeMS(int delay)
{
    this->enable = true;
    this->delay = delay * 1000;
}

void task::setDisable()
{
    this->enable = false;
}
void task::setEnable()
{
    this->enable = true;
}
bool task::idle()
{
    if (this->vidle)
    {
        this->vidle = false;
        return true;
    }
    return false;
}

void task::run()
{
    if (this->enable)
    {

        if ((TASK_TIME_NOW_MC - this->prevMills) >= this->delay)
        {
            if (this->toggle)
            {
                this->toggle = false;
            }
            else
            {
                this->toggle = true;
            }
            this->fnc();
            this->vidle = true;
            this->prevMills = TASK_TIME_NOW_MC;
        }
    }
}

void task::Exc(THandlerFunction fn)
{
    this->fnc = fn;
}

thread *thread::NewTask(int delay)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].running)
        {
            this->idleID = a;
            break;
        }
    }
    Task[this->idleID].SetTask();
    Task[this->idleID].setTimeMS(delay);
    return this;
}
thread *thread::NewTaskC(int delay)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].running)
        {
            this->idleID = a;
            break;
        }
    }
    Task[this->idleID].SetTask();
    Task[this->idleID].setTime(delay);
    return this;
}
bool thread::Idle()
{
    return Task[this->idleID].idle();
}

bool thread::IdleToggle()
{
    return Task[this->idleID].toggle;
}

void thread::StopTask()
{
    Task[this->idleID].KillTask();
}

void thread::Enable()
{
    Task[this->idleID].setEnable();
}
void thread::Disable()
{
    Task[this->idleID].setDisable();
}
void thread::Exc(task::THandlerFunction fn)
{
    Task[this->idleID].Exc(fn);
}
