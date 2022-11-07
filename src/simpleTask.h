#ifndef __TASK__
#define __TASK__
#define TASK_TIME_NOW_MC (micros())
#define TASK_TIME_NOW_MS (millis())

#include <memory>

#define TASK_MOD_MC
#define TASK_MAX 10

// typedef std::function<void(void)> THandlerFunction;

class task
{
private:
    unsigned long prevMills;
    int delay = 0;
    bool vidle = false;

public:
    typedef std::function<void(void)> THandlerFunction;
    THandlerFunction fnc;
    void Exc(THandlerFunction);
    void SetTask();
    void KillTask();
    bool idle();
    void setTime(int);
    void setTimeMS(int);
    void setDisable();
    void setEnable();
    bool running = false;
    bool enable = false;
    bool toggle = false;
    void run();
};

struct thread
{
    int idleID = 0;
    thread *NewTask(int delay);
    thread *NewTaskC(int delay);
    void StopTask();
    bool Idle();
    void Disable();
    void Enable();
    bool IdleToggle();
    void Exc(task::THandlerFunction);
};

extern task Task[TASK_MAX];
#endif
