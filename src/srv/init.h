#ifndef __SERVICE__
#define __SERVICE__

#include <Arduino.h>
#include "../simpleTask.h"
#include "../log.h"

void Srvinit();
void SrvTes();

void SrvSerialInit();
String SrvSerialRead();
void SrvExcSerialExc(task *Arg);
bool SrvSerialIdle();

void srvExcInit();
void SrvExcTes(task *Arg);
void SrvExcSerial(task *Arg);

void RunInit();

#endif