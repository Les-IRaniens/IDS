#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils/list.h"
#include "populate.h"

#include "rule.h"

RuleList
parse_rule(StrList rules)
{
    size_t i;
    char *rule_raw;
    char *wanted_protocole;
    char *token;
    char *key;
    char *value;
    char *save;
    char content[CONTENT_LENGTH];
    
    Rule rule;
    RuleList list;

    list.rules  = (Rule *) malloc(sizeof(Rule) * rules.length);
    list.length = rules.length;

    for (i = 0; i < rules.length; i++)
    {
        rule_raw = rules.raw[i];
        memset(content, 0, CONTENT_LENGTH);

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

        rule.content[0] = 0;
        rule.client_side[0] = 0;

        token = strtok(NULL, " ");

        while (token != NULL)
        {
            strcat(content, token);
            content[strlen(content)] = ' ';
            token = strtok(NULL, " ");
        }
        
        memmove(content, content+1, strlen(content)-1);
        content[strlen(content)-5] = '\0';

        token = strtok_r(content, ";", &save);
        while (token != NULL)
        {
            if (token[0] == ' ')
            {
                memmove(token, token+1, strlen(token)-1);
                token[strlen(token)-1] = 0;
            }

            key = strtok(token, ":");
            value = strtok(NULL, ":");

            memmove(value, value+1, strlen(value)-1);
            value[strlen(value)-2] = 0;

            if (strcmp(key, "msg") == 0)
            {
                strcpy(rule.msg, value);
            }

            if (strcmp(key, "content") == 0)
            {
                strcpy(rule.content, value);
            }

            if (strcmp(key, "client-side-content") == 0)
            {
                strcpy(rule.client_side, value);
            }

            token = strtok_r(NULL, ";", &save);
        }

        list.rules[i] = rule;
    }

    return list;
}

bool 
is_in_context(Rule rule, void *packet, Protocole proto)
{
    ETHER_Frame ether = *((ETHER_Frame *) packet);

    if (rule.protocol != proto)
    {
        return false;
    }

    if (strcmp(rule.ip_dest, "any") != 0 &&
        strcmp(rule.ip_dest, ether.data.destination_ip) != 0)
    {
        return false;
    }

    if (strcmp(rule.ip_src, "any") != 0 &&
        strcmp(rule.ip_dest, ether.data.source_ip) != 0)
    {
        return false;
    }

    if (ether.proto == TCP)
    {
        if (strcmp(rule.port_dest, "any") != 0 && 
            atoi(rule.port_dest) != ether.data.tcp_data.destination_port)
        {
            return false;
        }

        if (strcmp(rule.port_src, "any") != 0 && 
            atoi(rule.port_src) != ether.data.tcp_data.source_port)
        {
            return false;
        }
    }

    return true;
}


void 
free_rules(RuleList *lst)
{
    free(lst->rules);
}