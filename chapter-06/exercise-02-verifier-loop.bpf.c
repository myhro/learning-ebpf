#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

SEC("xdp")
int xdp_hello(struct xdp_md *ctx) {
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;

  // Attempt to read outside the packet
  // data_end++;

   // This is a loop that will pass the verifier
   for (int i=0; i < 10; i++) {
      bpf_printk("Looping %d", i);
   }

   // This is a loop that will fail the verifier
   // for (int i=0; i < c; i++) {
   //    bpf_printk("Looping %d", i);
   // }

  // Comment out the next two lines and there won't be a return code defined
  bpf_printk("%x %x", data, data_end);
  return XDP_PASS;
}

// Removing the license section means the verifier won't let you use
// GPL-licensed helpers
char LICENSE[] SEC("license") = "Dual BSD/GPL";
