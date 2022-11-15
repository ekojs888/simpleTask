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

void task::setDisable()
{
    this->enable = false;
}
void task::setEnable()
{
    this->enable = true;
}
bool task::GetEnable()
{
    return this->enable;
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
bool task::getToggle()
{
    return this->toggle;
}
void task::SetRunning(bool sts)
{
    this->running = sts;
}
bool task::GetRunning()
{
    return this->running;
}
void task::runFunc()
{
    if (this->funcOk)
    {
        this->fnc(this);
        switch (this->mode)
        {
        case TASK_MODE_ONESHOOT:
            this->enable = false;
            break;
        case TASK_MODE_DEFAULT:
            break;
        default:
            break;
        }
    }
}
void task::runToggle()
{
    if (this->toggle)
    {
        this->toggle = false;
    }
    else
    {
        this->toggle = true;
    }
}

void task::run()
{
    if (this->enable)
    {
        // run loop func
        if ((TASK_TIME_NOW_MC - this->prevMills) >= this->delay && this->delay != 0)
        {
            this->runToggle();
            this->runFunc();
            this->vidle = true;
            this->prevMills = TASK_TIME_NOW_MC;
        }
    }
}

bool task::GetShootOne()
{
    return this->funcShootOne;
}

task *task::Exc(HandlerFunc fn)
{
    this->fnc = fn;
    this->setDisable();
    return this;
}
task *task::Loop(HandlerFunc fn)
{
    this->funcOk = true;
    this->fnc = fn;
    return this;
}
task *task::Loop(HandlerFunc fn, int delay)
{
    this->funcOk = true;
    this->fnc = fn;
    this->delay = delay;
    return this;
}

task *task::SetMode(uint8_t mode)
{
    this->mode = mode;
    return this;
}
task *task::SetMode(uint8_t mode, String after)
{
    this->setDisable();
    this->mode = mode;
    this->runAfter = after;
    return this;
}
uint8_t task::GetMode()
{
    return this->mode;
}
// void task::SetName(String name)
// {
//     this->name = name;
// }
task *task::SetName(String name)
{
    this->name = name;
    return this;
}
int task::GetID()
{
    return this->id;
}
void task::SetID(int id)
{
    this->id = id;
}
int task::GetPriority()
{
    return this->priority;
}
void task::SetPriority(int pr)
{
    if (pr > 5)
        pr = 5;
    this->priority = pr;
}
String task::GetName()
{
    return this->name;
}
task *task::SetRunAfter(String after)
{
    this->setDisable();
    this->runAfter = after;
    return this;
}
String task::GetRunAfter()
{
    return this->runAfter;
}

task *task::GetTask(String name)
{
    int a;
    for (a = 0; a < TASK_MAX; a++)
    {
        if (Task[a].GetRunning() && Task[a].GetName() == name)
        {
            break;
        }
    }
    return &Task[a];
}
task *task::GetTask(int id)
{
    return &Task[id];
}

void task::RunInit()
{
    this->fnc(this);
    this->setEnable();
}
