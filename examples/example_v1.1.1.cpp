#include <Arduino.h>
#include <simpleTask.h>
// add lib_defs = -D LOG_EN=true in platformio.ini
#include <simpleLog.h>

// this example for version ^1.1.1

void tes2(task *Arg);

int no = 0;
void tes1(task *Arg)
{
    pinMode(2, OUTPUT);
    Serial.println("test first");
    Arg->Loop(tes2, 500 * TASK_DELAY_MS);
}
void tes2(task *Arg)
{
    if (no >= 10)
    {
        digitalWrite(2, Arg->getToggle());
        Serial.println("delay loop");
    }
    else
    {
        Serial.println(no);
        no++;
    }
}
void tes3(task *Arg)
{
    digitalWrite(2, Arg->getToggle());
    Serial.println("delay loop 3");
    // Arg->Loop(tes2);
}

// this declaration function routing
// func _SimpleTask();

void _SimpleTask()
{
    Serial.begin(9600);
    thread t1;
    t1.NewTask(TASK_PRIORTY_5, "Init", tes1);
    t1.NewTask(TASK_PRIORTY_0, "Init2", tes3);
}
