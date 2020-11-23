#include <checkuser.h>
#include <unistd.h>
#include <sys/types.h>

bool
is_root(void)
{
    uid_t id = getuid();
    return id == 0;
}


