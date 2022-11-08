#include <Arduino.h>
#include "simpleTask.h"

task Task[TASK_MAX];

void task::KillTask()
{
    this->running = false;
}
void task::KillTask(int id)
{
    Task[id].running = false;
}
void task::KillTask(String name)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (Task[a].getRunning() && Task[a].name == name)
        {
            Task[a].running = false;
            Serial.println(Task[a].name);
            break;
        }
    }
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
bool task::getToggle()
{
    return this->toggle;
}
bool task::getRunning()
{
    return this->running;
}
void task::runFunc()
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
void task::run()
{
    if (this->enable)
    {
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
            case 0:
                this->runFunc();
                this->enable = false;
                break;
            case 1:
                this->runFunc();
                break;
            default:
                break;
            }
            this->vidle = true;
            this->prevMills = TASK_TIME_NOW_MC;
        }
    }
}

void task::Exc(HandlerFunc fn)
{
    this->fnc = fn;
}

void task::Exc(HandlerFunc2 fn)
{
    this->handFuncPointer = true;
    this->fnc2 = fn;
}