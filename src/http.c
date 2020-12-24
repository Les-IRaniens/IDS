#include "http.h"
#include "utils/list.h"
#include "utils/macro.h"

#include <stdlib.h>
#include <assert.h>

HttpRequestType
is_http_request(char *str, int next_package)
{
    if (strstr(str, "GET") != NULL || strstr(str, "POST") != NULL)
    {
        return HTTP_CLIENT_SIDE;
    }
    else if (strstr(str, "HTTP/1.0") != NULL || strstr(str, "HTTP/1.1") != NULL || strstr(str, "HTTP/2.0") != NULL)
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

    __unused(rules);

    printf("%s\n", ether.data.data.data);

    if (type == HTTP_SERVER_SIDE)
    {
        split = split_to_strlist((char *) ether.data.data.data, "\n");

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
        *next_package -= ether.data.data.data_length;
        assert(*next_package >= 0);
    }
}