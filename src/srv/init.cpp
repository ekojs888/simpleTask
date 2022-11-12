#include "init.h"

void RunInit()
{
    Srvinit();
    SrvTes();
}

void Srvinit()
{
    thread t1;
    auto ts = t1.NewTask(1000, TASK_PRIORTY_0);
    ts->SetName("Init");
    ts->SetMode(TASK_MODE_ONESHOOT);
    ts->Exc(srvExcInit);
}

void srvExcInit()
{
    Log.init(9600);
    Log.Print("app task v1.1.0");
}