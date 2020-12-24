#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils/list.h"

#include "rule.h"

RuleList
parse_rule(StrList rules)
{
    size_t i;
    char *rule_raw;
    char *wanted_protocole;
    
    Rule rule;
    RuleList list;

    list.rules  = (Rule *) malloc(sizeof(Rule) * rules.length);
    list.length = rules.length;

    for (i = 0; i < rules.length; i++)
    {
        rule_raw = rules.raw[i];

        strcpy(rule.action, strtok(rule_raw, " "));

        wanted_protocole = strtok(NULL, " ");

        if (strcmp(wanted_protocole, "http") == 0 || strcmp(wanted_protocole, "HTTP") == 0)
        {
            rule.protocol = HTTP;
        }
        else if (strcmp(wanted_protocole, "ftp") == 0 || strcmp(wanted_protocole, "FTP") == 0)
        {
            rule.protocol = FTP;
        }
        else if (strcmp(wanted_protocole, "udp") == 0 || strcmp(wanted_protocole, "UDP") == 0)
        {
            rule.protocol = UDP;
        }
        else if (strcmp(wanted_protocole, "tcp") == 0 || strcmp(wanted_protocole, "TCP") == 0)
        {
            rule.protocol = TCP;
        }
        else 
        {
            assert(0);
        }

        
        strcpy(rule.ip_src, strtok(NULL, " "));
        strcpy(rule.port_src, strtok(NULL, " "));
        strtok(NULL, " ");
        strcpy(rule.ip_dest, strtok(NULL, " "));
        strcpy(rule.port_dest, strtok(NULL, " "));

        /*token = strtok(NULL, " ");

        while (token != NULL)
        {
            push_format_string(&action, "%s ", token);
            token = strtok(NULL, " ");
        }

        pop_tovoid_char_string(&action, 4);
        actions = as_str_string(&action);
        actions++;
        
        strcpy(rule.content, as_str_string(&action));
        list.rules[i] = rule;

        free_string(&action);*/
    }

    return list;
}

void 
free_rules(RuleList *lst)
{
    free(lst->rules);
}