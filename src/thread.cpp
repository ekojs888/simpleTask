#include <Arduino.h>
#include "simpleTask.h"

void thread::searchID()
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->ID = a;
            break;
        }
    }
}
task *thread::NewTask(int delay)
{
    this->searchID();
    if (this->ID != -1)
    {
        Task[this->ID].SetID(this->ID);
        Task[this->ID].SetTask();
        Task[this->ID].setTime(delay);
    }
    return this->GetTask();
}
task *thread::NewTask(int delay, uint8_t priority)
{
    this->searchID();
    if (this->ID != -1)
    {
        this->GetTask()->SetPriority(priority);
        this->GetTask()->SetID(this->ID);
        this->GetTask()->SetTask();
        this->GetTask()->setTime(delay);
    }
    return this->GetTask();
}
task *thread::NewTask(int delay, uint8_t priority, String name, task::HandlerFunc fn)
{
    this->searchID();
    if (this->ID != -1)
    {
        this->GetTask()->SetPriority(priority);
        this->GetTask()->SetID(this->ID);
        this->GetTask()->SetTask();
        this->GetTask()->setTime(delay);
        this->GetTask()->Exc(fn);
    }
    return this->GetTask();
}
task *thread::GetTask()
{
    return &Task[this->ID];
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
