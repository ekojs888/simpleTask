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
public:
    String name, runAfter;
    int id;
    uint8_t priority = 0; // 0,1,2,3,4
    uint8_t mode = TASK_MODE_DEFAULT;

    typedef std::function<void(void)> HandlerFunc;
    typedef std::function<void(task *arg)> HandlerFunc2;

    void Exc(HandlerFunc2 fn);
    void Exc(HandlerFunc);
    void SetTask();
    void KillTask();
    void KillTask(int id);
    void KillTask(String name);
    void setTime(int);
    void setTimeMS(int);
    void setMode(int);

    bool getToggle();
    bool getRunning();
    void setDisable();
    void setEnable();
    bool idle();
    void run();

private:
    unsigned long prevMills;
    int delay = 0;

    bool vidle = false;
    bool toggle = false;
    bool running = false;
    bool enable = false;
    bool handFuncPointer = false;
    HandlerFunc fnc;
    HandlerFunc2 fnc2;
    void runFunc();
};

struct thread
{
private:
public:
    int idleID = 0;

    void NewTask(int delay);
    void NewTask(int delay, uint8_t priority);
    void NewTask(int delay, uint8_t priority, bool us);
    void TaskName(String name);
    void Mode(uint8_t mode);
    void Mode(uint8_t mode, String after);
    void SetAfter(String after);
    void StopTask();
    void Exc(task::HandlerFunc);
    void Exc(task::HandlerFunc2);
};

extern task Task[TASK_MAX];

void _TaskRunning();
#endif