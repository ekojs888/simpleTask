#ifndef __SERVICE__
#define __SERVICE__

#include <Arduino.h>
#include "../simpleTask.h"
#include "../log.h"

void Srvinit();
void SrvTes();

void srvExcInit();
void SrvExcTes(task *Arg);

void RunInit();

#endif