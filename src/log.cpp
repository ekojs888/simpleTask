#include "log.h"

logging Log;

void logging::init(unsigned long baud)
{
#ifdef LOG_EN
    Serial.begin(baud);
#else
    NOP();
#endif
}
int logging::Print(const char *format, ...)
{
    int len = 0;
#ifdef LOG_EN
    // this refrence from aruino print
    char loc_buf[64];
    char *temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    len = vsnprintf(temp, sizeof(loc_buf), format, copy);
    va_end(copy);
    if (len < 0)
    {
        va_end(arg);
        return 0;
    };
    if (len >= sizeof(loc_buf))
    {
        temp = (char *)malloc(len + 1);
        if (temp == NULL)
        {
            va_end(arg);
            return 0;
        }
        len = vsnprintf(temp, len + 1, format, arg);
    }
    va_end(arg);
    len = Serial.write((uint8_t *)temp, len);
    if (temp != loc_buf)
    {
        free(temp);
    }
#endif
    return len;
}