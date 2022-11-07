#include <Arduino.h>
#include <simpleTask.h>

thread task1;

bool sts;
void flipFlop()
{
  digitalWrite(GPIO_NUM_2, sts);
  sts = !(sts);
}
void setup()
{
  // put your setup code here, to run once:
  pinMode(GPIO_NUM_2, OUTPUT);
  // init task delay every 1000 ms
  task1.NewTask(1000);
  // exc if time
  task1.Exc(flipFlop);
}

void loop()
{
  // put your main code here, to run repeatedly:
  _TaskRunning();
}
