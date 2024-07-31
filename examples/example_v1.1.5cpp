#include <Arduino.h>
#include <simpleTask.h>

//if not use void main(); and void loop(); define TASK_MOD;
//#define TASK_MOD; 
// or 
//take in platfromio.ini add
// build_flags =
//   -D TASK_MOD="MyDevice"
//

void task4(task *Arg)
{
    Arg->varInt[0]++;
    Serial.printf("task4:%d\n\r",Arg->varInt[0]);
    digitalWrite(27, Arg->getToggle());
}

void task3(task *Arg)
{
    Arg->varInt[0] = 1;
    Arg->Loop(task4, 200 * TASK_DELAY_MS);
}

void task2(task *Arg)
{
    Serial.printf("task2:%d\n\r",Arg->varInt[0]++);
    digitalWrite(26, Arg->getToggle());
}

void task1(task *Arg)
{
    Serial.begin(9600);

    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    Arg->varInt[0] = 100;
    Arg->Loop(task2, 500 * TASK_DELAY_MS);
}

void _SimpleTask()
{
    thread t1;
    t1.NewTask(TASK_PRIORTY_5, "Init", task1);
    t1.NewTask(TASK_PRIORTY_1, "test2", task3);
}

