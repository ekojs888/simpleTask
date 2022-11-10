#include <Arduino.h>
#include <simpleTask.h>

void tesInit()
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    Serial.println("app task v1.1.0");
}

void tesBar(task *Arg)
{
    bool sts = Arg->getToggle();
    digitalWrite(2, sts);
}
void tesRun2(task *Arg)
{
    Serial.println("hallow word");
}

int ac = 100;
void tesRun(task *Arg)
{
    if (ac <= 0)
    {
        Arg->Exc(tesRun2);
        Arg->setTimeMS(1000);
        Arg->SetMode(TASK_MODE_ONESHOOT);

        auto ts = Arg->GetTask("Bar");
        ts->SetRunAfter(Arg->GetName());
        ts->setEnable();
    }
    else
    {
        bool sts = Arg->getToggle();
        digitalWrite(2, sts);
        ac--;
    }
}

thread t1, t2, t3;

void setup()
{
    auto ts = t1.NewTask(1000, 5);
    ts->SetName("Foo");
    ts->SetMode(TASK_MODE_ONESHOOT);
    ts->Exc(tesInit);

    ts = t2.NewTask(200, 0);
    ts->SetName("Flop");
    ts->SetRunAfter("Foo");
    ts->SetMode(TASK_MODE_DEFAULT);
    ts->Exc(tesRun);

    ts = t3.NewTask(1000, 5);
    ts->SetName("Bar");
    ts->SetMode(TASK_MODE_DEFAULT);
    ts->Exc(tesBar);
    ts->setDisable();
}

void loop()
{
    _TaskRunning();
}