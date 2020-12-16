#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lists/list.h>
#include <string/string.h>

#include "rule.h"

RuleList
parse_rule(List rules)
{
    size_t i;
    char *rule_raw;
    char *token;
    char *actions;
    String action;
    
    Rule rule;
    RuleList list;

    list.rules  = (Rule *) malloc(sizeof(Rule) * len_list(&rules));
    list.length = len_list(&rules);

    for (i = 0; i < len_list(&rules); i++)
    {
        init_string(&action);
        rule_raw = (char *) get_list_element(&rules, i).ptr;

        strcpy(rule.action, strtok(rule_raw, " "));
        strcpy(rule.protocol, strtok(NULL, " "));
        strcpy(rule.ip_src, strtok(NULL, " "));
        strcpy(rule.port_src, strtok(NULL, " "));
        strtok(NULL, " ");
        strcpy(rule.ip_dest, strtok(NULL, " "));
        strcpy(rule.port_dest, strtok(NULL, " "));

        token = strtok(NULL, " ");

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

        free_string(&action);
    }

    return list;
}

void 
free_rules(RuleList *lst)
{
    free(lst->rules);
}