#include "network.h"
#include <bpf/bpf_helpers.h>

SEC("xdp")
int ping(struct xdp_md *ctx) {
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;

    if (is_ping_request(data, data_end)) {
        bpf_printk("Got ping request");
    } else if (is_ping_response(data, data_end)) {
        bpf_printk("Got ping response");
    }

    return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
