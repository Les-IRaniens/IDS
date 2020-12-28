#include "http.h"
#include "utils/list.h"
#include "utils/macro.h"
#include "utils/log.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

HttpRequestType
is_http_request(char *str, int next_package)
{
    if (strstr(str, "GET") != NULL || strstr(str, "POST") != NULL)
    {
        return HTTP_CLIENT_SIDE;
    }
    else if (strstr(str, "HTTP/1.0") != NULL || strstr(str, "HTTP/1.1") != NULL
             || strstr(str, "HTTP/2.0") != NULL)
    {
        return HTTP_SERVER_SIDE;
    }
    else if (next_package > 0)
    {
        return HTTP_CONTENT;
    }

    return HTTP_NOT_HTTP;
}

void 
check_rule_http(RuleList rules, ETHER_Frame ether, HttpRequestType type, int *next_package)
{
    size_t i;
    StrList split;

    for (i = 0; i < rules.length; i++)
    {
        if (rules.rules[i].protocol != HTTP)
        {
            continue;
        }

        if (!is_in_context(rules.rules[i], &ether, HTTP))
        {
            continue;
        }
       
        if (rules.rules[i].content[0] == 0 && rules.rules[i].client_side[0] == 0)
        {
            log_ids(rules.rules[i].msg);
        }

        if (rules.rules[i].content[0] != 0 && 
            strstr((char *) ether.data.tcp_data.data, rules.rules[i].content))
        {
            log_ids(rules.rules[i].msg);
        }

        if (rules.rules[i].client_side[0] != 0 && type == HTTP_CLIENT_SIDE &&
            strstr((char *) ether.data.tcp_data.data, rules.rules[i].client_side))
        {
            log_ids(rules.rules[i].msg);
        }
    }

    if (type == HTTP_SERVER_SIDE)
    {
        split = split_to_strlist((char *) ether.data.tcp_data.data, "\n");

        for (i = 0; i < split.length; i++)
        {
            if (strstr(split.raw[i], "Content-Length") != NULL)
            {
                strtok(split.raw[i], ": ");
                *next_package = atoi(strtok(NULL, ": "));

                assert(*next_package > 0);
            }
        }
    }

    else if (type == HTTP_CONTENT)
    {
        *next_package -= ether.data.tcp_data.data_length;
        
        if (*next_package < 0)
        {
            *next_package = 0;
        }
    }
}