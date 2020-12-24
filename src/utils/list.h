#ifndef _IDS_LIST_H_
#define _IDS_LIST_H_

#define DEFAULT_LIST_CAPACTY 32

#include <stddef.h>

typedef struct 
{
    char **raw;
    size_t length;
    size_t capacity;
} StrList;

void init_str_list(StrList *);
void append_str_list(StrList *, const char *);
void free_str_list(StrList *);
StrList split_to_strlist(char *, const char *);

#endif /* !_IDS_LIST_H_ */