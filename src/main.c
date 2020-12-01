#include <string.h>
#include <stdio.h>
#include <pcap/pcap.h>

#include "scan.h"
#include "checkuser.h"
#include "usage.h"

int 
main(int argc, char* argv[])
{
    char *interface = NULL;

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
	else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interface"))
    {
	    if (argc == 2)
        {
	        fprintf(stderr, "Please specify an interface !\n");
	        return 1;
        }

	    interface = argv[2];
    }

	if (!is_root())
	{
		fprintf(stderr, "You must be root !\n");
		return 1;
	}

	scan_network(interface);

	return 0;
}