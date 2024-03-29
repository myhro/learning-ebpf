//go:build ignore

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int hello() {
    bpf_printk("Hello World");
    return 0;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
