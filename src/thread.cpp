#include <Arduino.h>
#include "simpleTask.h"

task *thread::NewTask(int delay)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->ID = a;
            break;
        }
    }
    if (this->ID != -1)
    {
        Task[this->ID].SetID(this->ID);
        Task[this->ID].SetTask();
        Task[this->ID].setTimeMS(delay);
    }
    return this->GetTask();
}
task *thread::NewTask(int delay, uint8_t priority)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->ID = a;
            break;
        }
    }
    if (this->ID != -1)
    {
        this->GetTask()->SetPriority(priority);
        this->GetTask()->SetID(this->ID);
        this->GetTask()->SetTask();
        this->GetTask()->setTimeMS(delay);
    }
    return this->GetTask();
}
task *thread::NewTask(int delay, uint8_t priority, bool us)
{
    for (int a = 0; a < TASK_MAX; a++)
    {
        if (!Task[a].GetRunning())
        {
            this->ID = a;
            break;
        }
    }
    if (this->ID != -1)
    {
        this->GetTask()->SetPriority(priority);
        this->GetTask()->SetID(this->ID);
        this->GetTask()->SetTask();
        if (us)
            this->GetTask()->setTime(delay);
        else
            this->GetTask()->setTimeMS(delay);
    }
    return this->GetTask();
}

// void thread::Exc(task::HandlerFunc fn)
// {
//     Task[this->ID].Exc(fn);
// }
// void thread::Exc(task::HandlerFunc2 fn)
// {
//     Task[this->ID].Exc(fn);
// }
// void thread::Mode(uint8_t mode)
// {
//     Task[this->ID].setMode(mode);
// }
// void thread::Mode(uint8_t mode, String after)
// {
//     Task[this->ID].setDisable();
//     Task[this->ID].SetMode(mode);
//     Task[this->ID].SetRunAfter(after);
// }
// void thread::TaskName(String name)
// {
//     Task[this->ID].SetName(name);
// }
// void thread::SetAfter(String after)
// {
//     Task[this->ID].setDisable();
//     Task[this->ID].SetRunAfter(after);
// }

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

// void thread::Kill(String name)
// {
//     for (int a = 0; a < TASK_MAX; a++)
//     {
//         if (Task[a].GetRunning() && Task[a].GetName() == name)
//         {
//             Task[a].SetRunning(false);
//             Serial.println(Task[a].GetName());
//             break;
//         }
//     }
// }

// void thread::Kill(int id)
// {
//     Task[id].SetRunning(false);
// }