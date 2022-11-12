#ifndef __TASK__
#define __TASK__
#define TASK_TIME_NOW_MC (micros())
#define TASK_TIME_NOW_MS (millis())

#define TASK_MOD_MC
#define TASK_MAX 100
#define TASK_PRIORTY 6

#define TASK_MODE_ONESHOOT 0
#define TASK_MODE_DEFAULT 1

#define TASK_PRIORTY_0 0
#define TASK_PRIORTY_1 1
#define TASK_PRIORTY_2 2
#define TASK_PRIORTY_3 3
#define TASK_PRIORTY_4 4
#define TASK_PRIORTY_5 5

class task
{
public:
    typedef void (*HandlerFunc)(void);
    typedef void (*HandlerFunc2)(task *arg);

    void SetName(String name);
    String GetName();
    void SetMode(uint8_t mode);
    void SetMode(uint8_t mode, String after);
    uint8_t GetMode();
    void SetRunAfter(String after);
    String GetRunAfter();
    void SetID(int id);
    int GetID();
    void SetPriority(int pr);
    int GetPriority();
    void SetRunning(bool sts);
    bool GetRunning();

    void SetTask();
    void setTime(int);
    void setTimeMS(int);
    void setMode(int);

    void KillTask();
    void Exc(HandlerFunc2 fn);
    void Exc(HandlerFunc);
    // void ExcInt(HandlerFunc);
    // void ExcInt(HandlerFunc2 fn);

    bool getToggle();
    void setDisable();
    void setEnable();
    bool GetEnable();
    bool GetShootOne();
    bool idle();
    void run();

    task *GetTask(int id);
    task *GetTask(String name);

private:
    unsigned long prevMills;
    int delay = 0;

    bool vidle = false;
    bool toggle = false;
    bool running = false;
    bool enable = false;
    bool handFuncPointer = false;
    bool funcIntOk = false;
    bool funcOk = false;
    bool funcShootOne = true;
    // HandlerFunc fncInit;
    // HandlerFunc2 fncInit2;
    HandlerFunc fnc;
    HandlerFunc2 fnc2;

    String name, runAfter;
    int id = -1;
    uint8_t priority = 5; // 0,1,2,3,4
    uint8_t mode = TASK_MODE_DEFAULT;

    void runFunc();
};

struct thread
{
private:
    int ID = -1;

public:
    task *NewTask(int delay);
    task *NewTask(int delay, uint8_t priority);
    task *NewTask(int delay, uint8_t priority, bool us);

    task *GetTask();
    task *GetTask(int id);
    task *GetTask(String name);
};

extern task Task[TASK_MAX];

void _TaskRunning();
#endif