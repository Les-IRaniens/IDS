#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

void 
init_str_list(StrList *self)
{
    self->capacity = DEFAULT_LIST_CAPACTY;

    self->raw = (char **) malloc(sizeof(char *) * self->capacity);
    assert(self->raw != NULL);

    self->length = 0;
}

void 
append_str_list(StrList *self, const char *str)
{
    if (self->length + 1 == self->capacity)
    {
        self->capacity *= 1.5;
        self->raw = (char **) realloc(self->raw, self->capacity);
        assert(self->raw != NULL);
    }
    
    self->raw[self->length++] = strdup(str);
}

void 
free_str_list(StrList *self)
{
    size_t i;

    for (i = 0; i < self->length; i++)
    {
        free(self->raw[i]);
    }

    self->capacity = 0;
    self->length = 0;
    free(self->raw);
}

StrList 
split_to_strlist(char *str, const char *del)
{
    StrList lst;
    char *token = strtok(str, del);

    init_str_list(&lst);

    while (token != NULL)
    {
        append_str_list(&lst, token);
        token = strtok(NULL, del);
    }

    return lst;
}
