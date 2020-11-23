#include <unistd.h>
#include <sys/types.h>

#include "checkuser.h"

bool
is_root(void)
{
    uid_t id = getuid();
    return id == 0;
}


