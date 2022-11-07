#ifndef __TASK__
#define __TASK__
#define TASK_TIME_NOW_MC (micros())
#define TASK_TIME_NOW_MS (millis())
#include "config.h"
#include <memory>

#define TASK_MOD_MC
#define TASK_MAX 100
#define TASK_PRIORTY 6

// typedef std::function<void(void)> THandlerFunction;

enum modeExc
{
    OneShoot,
    Default,
};

class task
{
private:
    unsigned long prevMills;
    int delay = 0;
    bool vidle = false;

    bool running = false;
    bool enable = false;
    bool toggle = false;

public:
    uint8_t priority = 0; // 0,1,2,3,4
    modeExc mode = Default;
    uint8_t runAfter = -1;

    typedef std::function<void(void)> THandlerFunction;
    THandlerFunction fnc;
    void Exc(THandlerFunction);
    void SetTask();
    void KillTask();
    void setTime(int);
    void setTimeMS(int);

    bool getToggle();
    bool getRunning();
    void setDisable();
    void setEnable();
    bool idle();
    void run();
};

struct thread
{
    int idleID = 0;
    uint8_t priority = 0; // 0,1,2,3,4

    // rencana kedepan
    modeExc mode = Default;
    uint8_t runAfter = -1;

    // thread *NewTaskC(int delay);
    // bool Idle();
    // bool IdleToggle();
    // void Disable();
    // void Enable();

    thread *NewTask(int delay);
    thread *NewTask(int delay, uint8_t priority);
    void Mode(modeExc mode);
    void StopTask();
    void Exc(task::THandlerFunction);
};

extern task Task[TASK_PRIORTY][TASK_MAX];

void _TaskRunning();
#endif