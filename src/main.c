#include <string.h>
#include <stdio.h>

#include <utils/macro.h>
#include <checkuser.h>
#include <usage.h>

int 
main(int argc, char* argv[])
{
	if (argc == 1)
	{
		show_usage(argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		show_usage(argv[0]);
		return 0;
	}

	if (!is_root())
	{
		fprintf(stderr, "You must be root !\n");
		return 1;
	}

	return 0;
}