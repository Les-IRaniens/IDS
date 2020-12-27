#include <stdio.h>

#include "log.h"

void 
log_ids(const char *msg)
{
    printf("\033[31m[*]\033[0m %s\n", msg);
}