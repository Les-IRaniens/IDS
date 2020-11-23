#include <stdio.h>
#include <usage.h>
#include <libgen.h>

void 
show_usage(char *exe_path)
{
	printf("Usage: %s [OPTION] FILE.rule\n", basename(exe_path));
	printf("A simple intrusion detection system\n\n");
	printf("  -i, --interface\tSpecify the interface to capture\n");
	printf("  -h, --help\t\tDisplay this information\n\n");
}