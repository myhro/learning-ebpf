#include "vmlinux.h"
#include <bpf/bpf_endian.h>

/*
    The constants below are missing from 'vmlinux.h'. Including their actual
    definitions from '/usr/include/' might cause multiple 'typedef redefinition
    with different types' errors.
*/
// From include/uapi/linux/if_ether.h
int ETH_P_IP = 0x0800;
// From include/uapi/linux/icmp.h
int ICMP_ECHO = 8;

int is_ping_request(void *data, void *data_end) {
    struct ethhdr *eth = data;
    if ((void *) eth + sizeof(struct ethhdr) > data_end) {
        return 0;
    }

    if (bpf_ntohs(eth->h_proto) != ETH_P_IP) {
        return 0;
    }

    struct iphdr *iph = (void *) eth + sizeof(struct ethhdr);
    if ((void *) iph + sizeof(struct iphdr) > data_end) {
        return 0;
    }

    if (iph->protocol != IPPROTO_ICMP) {
        return 0;
    }

    struct icmphdr *icmph = (void *) iph + sizeof(struct iphdr);
    if ((void *) icmph + sizeof(struct icmphdr) > data_end) {
        return 0;
    }

    return icmph->type == ICMP_ECHO;
}
