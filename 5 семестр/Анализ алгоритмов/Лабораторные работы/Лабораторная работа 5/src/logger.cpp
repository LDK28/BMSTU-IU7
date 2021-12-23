#include "logger.h"

void set_time(tm *ti, size_t *ms)
{
    system_clock::time_point now = system_clock::now();
    system_clock::duration cast = now.time_since_epoch();

    cast -= duration_cast<seconds>(cast);
    *ms = cast.count();
    
    time_t tt = system_clock::to_time_t(now);
    *ti = *gmtime(&tt);
}