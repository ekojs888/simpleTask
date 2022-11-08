#include <Arduino.h>
#include "simpleTask.h"

task Task[TASK_PRIORTY][TASK_MAX];

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
bool task::getToggle()
{
    return this->toggle;
}
bool task::getRunning()
{
    return this->running;
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

            switch (this->mode)
            {
            case 0:
                this->fnc();
                this->enable = false;
                break;
            case 1:
                this->fnc();
                break;
            default:
                break;
            }
            this->vidle = true;
            this->prevMills = TASK_TIME_NOW_MC;
        }
    }
}

void task::Exc(THandlerFunction fn)
{
    this->fnc = fn;
}
