#include "scan.h"
#include "http.h"
#include "utils/macro.h"
#include "utils/list.h"

#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdlib.h>

static int next_package = 0;

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
        type = is_http_request((char *) ether.data.data.data, next_package);

        if (type != HTTP_NOT_HTTP)
        {
            check_rule_http(rules, ether, type, &next_package);
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