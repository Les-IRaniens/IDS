#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/list.h"

#include "rule.h"

RuleList
parse_rule(StrList rules)
{
    size_t i;
    char *rule_raw;
    
    Rule rule;
    RuleList list;

    list.rules  = (Rule *) malloc(sizeof(Rule) * rules.length);
    list.length = rules.length;

    for (i = 0; i < rules.length; i++)
    {
        rule_raw = rules.raw[i];

        strcpy(rule.action, strtok(rule_raw, " "));
        strcpy(rule.protocol, strtok(NULL, " "));
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