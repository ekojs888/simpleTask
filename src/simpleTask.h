#ifndef __TASK__
#define __TASK__
#define TASK_TIME_NOW_MC (micros())
#define TASK_TIME_NOW_MS (millis())

#define TASK_MOD_MC

#ifndef TASK_MAX_NUM
#define TASK_MAX 100
#else
#define TASK_MAX (TASK_MAX_NUM)
#endif

#define TASK_PRIORTY 6

#define TASK_MODE_ONESHOOT 0
#define TASK_MODE_DEFAULT 1

#define TASK_PRIORTY_0 0
#define TASK_PRIORTY_1 1
#define TASK_PRIORTY_2 2
#define TASK_PRIORTY_3 3
#define TASK_PRIORTY_4 4
#define TASK_PRIORTY_5 5

#define TASK_DELAY_MS 1000

class task
{
public:
    typedef void (*HandlerFunc)(task *arg);
    typedef void (*HandleFuncInit)(task *arg);

    task *SetName(String name);
    String GetName();
    task *SetMode(uint8_t mode);
    task *SetMode(uint8_t mode, String after);
    uint8_t GetMode();
    task *SetRunAfter(String after);
    String GetRunAfter();
    void SetID(int id);
    int GetID();
    void SetPriority(int pr);
    int GetPriority();
    void SetRunning(bool sts);
    bool GetRunning();

    void SetTask();
    void setTime(int);
    void setMode(int);

    void KillTask();
    task *Exc(HandlerFunc);

    bool getToggle();
    void setDisable();
    void setEnable();
    bool GetEnable();
    bool GetShootOne();
    bool idle();
    void run();

    task *GetTask(int id);
    task *GetTask(String name);

    // test
    task *Loop(HandlerFunc);
    task *Loop(HandlerFunc, int);
    void RunInit();
    // buat variabel dalam sebuah task
    int varInt[10];
    bool varBool[2];
private:
    unsigned long prevMills;
    int delay = 0;

    bool vidle = false;
    bool toggle = false;
    bool running = false;
    bool enable = false;
    bool handFuncPointer = false;
    bool funcOk = false;
    bool funcShootOne = true;

    HandlerFunc fnc;

    String name, runAfter;
    int id = -1;
    uint8_t priority = 5; // 0,1,2,3,4
    uint8_t mode = TASK_MODE_DEFAULT;

    void runToggle();
    void runFunc();
};

// void funcInitNull(task *Arg);

struct thread
{
private:
    int ID = -1;
    void searchID();

public:
    task *NewTask(uint8_t priority);
    task *NewTask(uint8_t priority, String name, task::HandlerFunc fn);

    task *GetTask();
    task *GetTask(int id);
    task *GetTask(String name);
};

extern task Task[TASK_MAX];

void _TaskRunInit();
void _TaskRunning();

void _SimpleTask(void);
#endif