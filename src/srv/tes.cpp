// #include "init.h"

// void SrvTes()
// {
//     thread t1;
//     auto ts = t1.NewTask(1000, TASK_PRIORTY_0);
//     ts->SetName("Tes");
//     ts->SetMode(TASK_MODE_DEFAULT);
//     ts->SetRunAfter("Init");
//     ts->Exc(SrvExcTes);
// }

// void SrvExcTes(task *Arg)
// {
//     if (Arg->GetShootOne())
//     {
//         Log.Print("init pin 2");
//         pinMode(GPIO_NUM_2, OUTPUT);
//     }
//     digitalWrite(GPIO_NUM_2, Arg->getToggle());
//     Log.Print("tes : %s\n", SrvSerialRead());
// }