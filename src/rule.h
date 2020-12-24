#ifndef _IDS_RULE_H_
#define _IDS_RULE_H_

#include "utils/list.h"

#define IP_ADDR_LEN_STR 16
#define PORT_LEN_STR 5
#define CONTENT_LENGTH 512
#define ACTION_LENGTH 64
#define PROT_LENGTH 64

typedef enum 
{
    HTTP,
    FTP,
    TCP,
    UDP
} Protocole;

typedef struct _RULE
{
    char action[ACTION_LENGTH];
    Protocole protocol;

    char ip_src[IP_ADDR_LEN_STR];
    char ip_dest[IP_ADDR_LEN_STR];
    char port_src[PORT_LEN_STR];
    char port_dest[PORT_LEN_STR];

    char content[CONTENT_LENGTH];      /* => Package content */
} Rule;

typedef struct _RULE_LIST
{
    Rule *rules;
    size_t length;
} RuleList;

RuleList parse_rule(StrList);
void free_rules(RuleList *);

#endif  /* !_IDS_RULE_H_ */