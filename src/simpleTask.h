#ifndef __TASK__
#define __TASK__
#define TASK_TIME_NOW_MC (micros())
#define TASK_TIME_NOW_MS (millis())
#include <memory>

#define TASK_MOD_MC
#define TASK_MAX 100
#define TASK_PRIORTY 6

#define TASK_MODE_ONESHOOT 0
#define TASK_MODE_DEFAULT 1

// typedef std::function<void(void)> THandlerFunction;

class task
{
private:
    unsigned long prevMills;
    int delay = 0;

    bool vidle = false;
    bool toggle = false;
    bool running = false;
    bool enable = false;

public:
    String name, runAfter;
    int id;
    uint8_t priority = 0; // 0,1,2,3,4
    uint8_t mode = TASK_MODE_DEFAULT;

    typedef std::function<void(void)> HandlerFunc;
    HandlerFunc fnc;
    void Exc(HandlerFunc);
    void SetTask();
    void KillTask();
    void setTime(int);
    void setTimeMS(int);
    void setMode(int);

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

    thread *NewTask(int delay);
    thread *NewTask(int delay, uint8_t priority);
    void TaskName(String name);
    void Mode(uint8_t mode);
    void Mode(uint8_t mode, String after);
    void StopTask();
    void Exc(task::HandlerFunc);
};

extern task Task[TASK_PRIORTY][TASK_MAX];

void _TaskRunning();
#endif