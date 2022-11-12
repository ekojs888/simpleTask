#ifndef __LOGGING__
#define __LOGGING__
#include <Arduino.h>

// #define LOG_EN

class logging
{
public:
    void init(unsigned long);
    int Print(const char *, ...);
};

extern logging Log;

#endif