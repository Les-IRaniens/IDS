#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lists/list.h>

#include "readrules.h"

List 
read_rules(const char *filename)
{
    List lst;
    ssize_t read;
    char *buffer;
    size_t BUFFER_SIZE = 128;

    FILE *f = fopen(filename, "r");
    buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    init_list(&lst);

    while((read = getline(&buffer, &BUFFER_SIZE, f)) != -1)
    {
        append_list(&lst, strdup(buffer), CHAR_PTR);
    }
    
    free(buffer);
    return lst;
}

