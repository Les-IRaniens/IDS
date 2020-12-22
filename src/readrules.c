#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readrules.h"
#include "utils/list.h"

StrList
read_rules(const char *filename)
{
    StrList lst;
    ssize_t read;
    char *buffer;
    size_t BUFFER_SIZE = 128;

    FILE *f = fopen(filename, "r");
    buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    init_str_list(&lst);

    while((read = getline(&buffer, &BUFFER_SIZE, f)) != -1)
    {
        append_str_list(&lst, buffer);
    }
    
    free(buffer);
    return lst;
}

