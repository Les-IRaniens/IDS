#include "scan.h"
#include "http.h"
#include "utils/macro.h"
#include "utils/list.h"
#include "utils/log.h"

#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdlib.h>

static int next_package = 0;

void
handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet)
{
    size_t i;
    ETHER_Frame ether;
    HttpRequestType type;
    RuleList rules = *((RuleList *) user);

    
    populate_packet_ds(header, packet, &ether);

    if (ether.proto == TCP && ether.data.tcp_data.data_length > 1)
    {
        type = is_http_request((char *) ether.data.tcp_data.data, next_package);

        if (type != HTTP_NOT_HTTP)
        {
            check_rule_http(rules, ether, type, &next_package);
        }

        for (i = 0; i < rules.length; i++)
        {
            if (!is_in_context(rules.rules[i], &ether))
            {
                continue;
            }

            if (rules.rules[i].content[0] == '\0')
            {
                log_ids(rules.rules[i].msg);
            }
            else if (strcmp(rules.rule[i].content, (const char *) ether.data.tcp_data.data) == 0)
            {
                log_ids(rules.rules[i].msg);
            }
        }
    }
    else if(ether.proto == UDP)
    {
        /* UDP */
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