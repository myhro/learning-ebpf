#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>

/*
    The constants below are missing from 'vmlinux.h'. Including their actual
    definitions from '/usr/include/' might cause multiple 'typedef redefinition
    with different types' errors.
*/
// From include/uapi/linux/if_ether.h
int ETH_P_IP = 0x0800;
// From include/uapi/linux/icmp.h
int ICMP_ECHOREPLY = 0;
int ICMP_ECHO = 8;

struct icmphdr *icmp_header(void *data, void *data_end) {
    struct ethhdr *eth = data;
    if ((void *) eth + sizeof(struct ethhdr) > data_end) {
        return NULL;
    }

    if (bpf_ntohs(eth->h_proto) != ETH_P_IP) {
        return NULL;
    }

    struct iphdr *iph = (void *) eth + sizeof(struct ethhdr);
    if ((void *) iph + sizeof(struct iphdr) > data_end) {
        return NULL;
    }

    if (iph->protocol != IPPROTO_ICMP) {
        return NULL;
    }

    struct icmphdr *icmph = (void *) iph + sizeof(struct iphdr);
    if ((void *) icmph + sizeof(struct icmphdr) > data_end) {
        return NULL;
    }

    return icmph;
}

int is_ping_request(void *data, void *data_end) {
    struct icmphdr *icmph = icmp_header(data, data_end);
    if (icmph == NULL) {
      return 0;
    }
    return icmph->type == ICMP_ECHO;
}

int is_ping_response(void *data, void *data_end) {
   struct icmphdr *icmph = icmp_header(data, data_end);
    if (icmph == NULL) {
      return 0;
    }
    return icmph->type == ICMP_ECHOREPLY;
}
