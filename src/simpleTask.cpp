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
        if (this->handFuncPointer)
        {
            this->fnc2(this);
        }
        else
        {
            this->fnc();
        }
    }
}

void task::run()
{
    if (this->enable)
    {
        // run loop func
        if ((TASK_TIME_NOW_MC - this->prevMills) >= this->delay && this->delay != 0)
        {
            if (this->toggle)
            {
                this->toggle = false;
            }
            else
            {
                this->toggle = true;
            }

            switch (this->mode)
            {
            case TASK_MODE_ONESHOOT:
                this->runFunc();
                this->enable = false;
                break;
            case TASK_MODE_DEFAULT:
                this->runFunc();
                break;
            default:
                break;
            }
            if (this->funcShootOne)
            {
                this->funcShootOne = false;
            }
            this->vidle = true;
            this->prevMills = TASK_TIME_NOW_MC;
        }
    }
}

bool task::GetShootOne()
{
    return this->funcShootOne;
}

void task::Exc(HandlerFunc fn)
{
    this->funcOk = true;
    this->fnc = fn;
}

void task::Exc(HandlerFunc2 fn)
{
    this->funcOk = true;
    this->handFuncPointer = true;
    this->fnc2 = fn;
}

// void task::ExcInt(HandlerFunc fn)
// {
//     this->funcIntOk = true;
//     this->fncInit = fn;
// }

// void task::ExcInt(HandlerFunc2 fn)
// {
//     this->funcIntOk = true;
//     this->handFuncPointer = true;
//     this->fncInit2 = fn;
// }

void task::SetMode(uint8_t mode)
{
    this->mode = mode;
}
void task::SetMode(uint8_t mode, String after)
{
    this->setDisable();
    this->mode = mode;
    this->runAfter = after;
}
uint8_t task::GetMode()
{
    return this->mode;
}
void task::SetName(String name)
{
    this->name = name;
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
void task::SetRunAfter(String after)
{
    this->setDisable();
    this->runAfter = after;
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