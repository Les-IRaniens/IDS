#include <stdio.h>
#include <syslog.h>

#include "log.h"

void 
log_ids(const char *msg)
{
    openlog("IDS", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, msg);
    closelog();
    
    printf("\033[31m[*]\033[0m %s\n", msg);
}