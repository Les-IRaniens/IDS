#include "scan.h"
#include "populate.h"
#include "utils/macro.h"
#include "utils/list.h"

#include <pcap/pcap.h>
#include <stdlib.h>
#include <stdbool.h>

static bool next_package = false;

typedef enum 
{
    CLIENT_SIDE,
    SERVER_SIDE,
    CONTENT,
    NOT_HTTP
} HttpRequestType;

HttpRequestType
is_http_request(char *str)
{
    if (strstr(str, "GET") != NULL || strstr(str, "POST") != NULL)
    {
        return CLIENT_SIDE;
    }
    else if (strstr(str, "HTTP/1.0") != NULL || strstr(str, "HTTP/1.1") != NULL || strstr(str, "HTTP/2.0") != NULL)
    {
        return SERVER_SIDE;
    }
    else if (next_package)
    {
        return CONTENT;
    }

    return NOT_HTTP;
}

void
handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet)
{
    ETHER_Frame ether;
    HttpRequestType type;
    RuleList rules = *((RuleList *) user);
    __unused(rules);
    
    populate_packet_ds(header, packet, &ether);

    if (ether.data.data.data_length > 0)
    {
        type = is_http_request((char *) ether.data.data.data);
        
        if (type != NOT_HTTP)
        {
            printf("OK");
            printf(" =================\n");
            printf("FROM: %s\n", ether.data.source_ip);
            printf("TO: %s\n", ether.data.destination_ip);
            printf("DATA: %s", ether.data.data.data);
            printf(" =================\n");
        }

        if (type == SERVER_SIDE)
        {
            printf("SERVER SIDE !\n");
        }
    }
}

void
scan_network(char *interface, RuleList rules)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *inter = pcap_create(interface, errbuf);

    if (inter == NULL) 
    {
        printf("%s\n", errbuf);
        pcap_close(inter);
        exit(1);
    }

    pcap_set_timeout(inter, 10);
    pcap_activate(inter);

    pcap_loop(inter, 0, handler, (u_char *) &rules);

    pcap_close(inter);
}