#include "scan.h"
#include "populate.h"
#include "utils/macro.h"

#include <pcap/pcap.h>
#include <stdlib.h>

void
handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet)
{

    ETHER_Frame ether;
    __unused(user);

    populate_packet_ds(header, packet, &ether);
}

void
scan_network(char *interface)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *inter = pcap_create(interface, errbuf);
    if (inter == NULL) {
        printf("%s\n", errbuf);
        pcap_close(inter);
        exit(1);
    }

    pcap_set_timeout(inter, 10);
    pcap_activate(inter);

    pcap_loop(inter, 0, handler, NULL);

    pcap_close(inter);
}