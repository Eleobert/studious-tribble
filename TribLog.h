#include <Logger.h>

Log& log()
{
    static Log l("tribal-log.log");
    l.printstd(true);
    return l;
}