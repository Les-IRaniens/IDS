#ifndef _IDS_HTTP_H_
#define _IDS_HTTP_H_

#include "scan.h"
#include "populate.h"
#include "utils/list.h"

typedef enum 
{
    HTTP_CLIENT_SIDE,
    HTTP_SERVER_SIDE,
    HTTP_CONTENT,
    HTTP_NOT_HTTP
} HttpRequestType;

HttpRequestType is_http_request(char *, int);
void check_rule_http(RuleList, ETHER_Frame, HttpRequestType, int*);

#endif /* !_IDS_HTTP_H_ */