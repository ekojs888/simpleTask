#include <Arduino.h>
#include <simpleTask.h>

thread task1, task2;

bool sts = false;
void flipFlop(task *Arg)
{
    Serial.println(sts);
    digitalWrite(GPIO_NUM_2, sts);
    sts = !(sts);
}
void testA(task *Arg)
{
    Serial.print(Arg->id);
    // kill task name
    Arg->KillTask("Bar");
    Serial.println("hallo is first task");
}
void setup()
{
    Serial.begin(9600);
    // put your setup code here, to run once:
    pinMode(GPIO_NUM_2, OUTPUT);
    // init task delay every 1000 ms
    task1.NewTask(1000, 1);
    // task name
    task1.TaskName("Bar");
    // set Mode after run
    task1.Mode(TASK_MODE_DEFAULT, "Foo");
    // exc if time
    task1.Exc(flipFlop);

    task2.NewTask(5000);
    task2.Mode(TASK_MODE_ONESHOOT);
    task2.TaskName("Foo");
    task2.Exc(testA);
}

void loop()
{
    // put your main code here, to run repeatedly:
    _TaskRunning();
}
