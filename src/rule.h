#ifndef _IDS_RULE_H_
#define _IDS_RULE_H_

#define IP_ADDR_LEN_STR 16
#define PORT_LEN_STR 5
#define MSG_LENGTH 512
#define CONTENT_LENGTH 512
#define ACTION_LENGTH 64
#define PROT_LENGTH 64

#include <lists/list.h>

typedef struct _RULE
{
    char action[ACTION_LENGTH];
    char protocol[PROT_LENGTH];

    char ip_src[IP_ADDR_LEN_STR];
    char ip_dest[IP_ADDR_LEN_STR];
    char port_src[PORT_LEN_STR];
    char port_dest[PORT_LEN_STR];

    char msg[MSG_LENGTH];          /* => Syslog */
    char content[CONTENT_LENGTH];      /* => Package content */
} Rule;

void parse_rule(List);

#endif  /* !_IDS_RULE_H_ */