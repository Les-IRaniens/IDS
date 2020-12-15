#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>
#include <lists/list.h>

#include "readrules.h"
#include "scan.h"
#include "checkuser.h"
#include "usage.h"
#include "rule.h"

int 
main(int argc, char* argv[])
{
    char *interface = NULL;
	char *file = NULL;
	List rules;

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
	else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--interface") == 0)
    {
	    if (argc == 2)
        {
	        fprintf(stderr, "Please specify an interface !\n");
	        return 1;
        }

	    interface = argv[2];
    }
	
	if (argc == 3)
	{
		fprintf(stderr, "Please open a file !\n");
		return 1;
	}

	file = argv[3];

	if (!is_root())
	{
		fprintf(stderr, "You must be root !\n");
		return 1;
	}

	(void) interface;
	rules = read_rules(file);
	parse_rule(rules);
	/* scan_network(interface); */

	free_list(&rules);
	return 0;
}