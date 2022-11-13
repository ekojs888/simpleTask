#include "init.h"
// #include <iostream>
// #include <functional>

// std::function<void(task *Arg)> fun;
char SrvSerialBuff[100];
bool SrvSerialIdleBuff;
byte incomingByte = 0;
int n = 0;

void SrvSerialInit()
{
    thread t1;
    auto ts = t1.NewTask(0, TASK_PRIORTY_0);
    ts->SetName("Serial");
    ts->SetMode(TASK_MODE_DEFAULT);
    ts->SetRunAfter("Init");
    ts->Exc(SrvExcSerialExc);
}
String SrvSerialRead()
{
    return SrvSerialBuff;
}
bool SrvSerialIdle()
{
    return SrvSerialIdleBuff;
}
void SrvExcSerialExc(task *Arg)
{
    // if (Arg->GetShootOne())
    // {
    //     Log.Print("init pin 2");
    //     pinMode(GPIO_NUM_2, OUTPUT);
    // }
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        incomingByte = Serial.read();
        if (incomingByte == 10)
        {
            // Serial.println(SrvSerialRead);
            SrvSerialIdleBuff = true;
            n = 0;
        }
        else
        {
            SrvSerialBuff[n++] = char(incomingByte);
            SrvSerialIdleBuff = false;
        }
    }
    else
    {
        memset(SrvSerialBuff, '\0', 100);
    }
}
