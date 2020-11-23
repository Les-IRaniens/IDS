#include <stdio.h>
#include <utils/macro.h>
#include <checkuser.h>

int 
main(int argc, char* argv[])
{
	__unused(argc);
	__unused(argv);
	
	if (!is_root())
	{
		fprintf(stderr, "You must be root !\n");
		return 1;
	}

	return 0;
}