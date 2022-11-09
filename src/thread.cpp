#include <Arduino.h>
#include "simpleTask.h"

void thread::NewTask(int delay)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        Task[this->idleID].SetID(this->idleID);
        Task[this->idleID].SetTask();
        Task[this->idleID].setTimeMS(delay);
    }
}
void thread::NewTask(int delay, uint8_t priority)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        Task[this->idleID].SetPriority(priority);
        Task[this->idleID].SetID(this->idleID);
        Task[this->idleID].SetTask();
        Task[this->idleID].setTimeMS(delay);
    }
}
void thread::NewTask(int delay, uint8_t priority, bool us)
{
    this->idleID = -1;
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->idleID = a;
            break;
        }
    }
    if (this->idleID != -1)
    {
        if (priority > 5)
            priority = 5;
        Task[this->idleID].SetPriority(priority);
        Task[this->idleID].SetID(this->idleID);
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
    Task[this->idleID].setMode(mode);
}
void thread::Mode(uint8_t mode, String after)
{
    Task[this->idleID].setDisable();
    Task[this->idleID].SetMode(mode);
    Task[this->idleID].SetRunAfter(after);
}
void thread::TaskName(String name)
{
    Task[this->idleID].SetName(name);
}
void thread::SetAfter(String after)
{
    Task[this->idleID].setDisable();
    Task[this->idleID].SetRunAfter(after);
}

task *thread::GetTask(String name)
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
task *thread::GetTask(int id)
{
    return &Task[id];
}

void thread::Kill(String name)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (Task[a].GetRunning() && Task[a].GetName() == name)
        {
            Task[a].SetRunning(false);
            Serial.println(Task[a].GetName());
            break;
        }
    }
}

void thread::Kill(int id)
{
    Task[id].SetRunning(false);
}