#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include "hello-buffer-config.h"
#include "hello-buffer-config.skel.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
    if (level >= LIBBPF_DEBUG)
        return 0;

    return vfprintf(stderr, format, args);
}

void handle_event(void *ctx, int cpu, void *data, unsigned int data_sz)
{
    struct data_t *m = data;

    printf("%-6d %-6d %-16s %-16s %s\n", m->pid, m->uid, m->command, m->path, m->message);
}

void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
    printf("lost event\n");
}

void update_config_map(struct bpf_map *config, __u32 uid, struct user_msg_t msg) {
    bpf_map_update_elem(bpf_map__fd(config), &uid, &msg, BPF_ANY);
}

int main()
{
    struct hello_buffer_config_bpf *skel;
    int err;
    struct perf_buffer *pb = NULL;

    libbpf_set_print(libbpf_print_fn);

    skel = hello_buffer_config_bpf__open_and_load();
    if (!skel) {
        printf("Failed to open BPF object\n");
        return 1;
    }

    update_config_map(skel->maps.my_config, 0, (struct user_msg_t){.message = "Hey root!"});
    update_config_map(skel->maps.my_config, 501, (struct user_msg_t){.message = "Hi user 501!"});

    err = hello_buffer_config_bpf__attach(skel);
    if (err) {
        fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
        hello_buffer_config_bpf__destroy(skel);
        return 1;
    }

    pb = perf_buffer__new(bpf_map__fd(skel->maps.output), 8, handle_event, lost_event, NULL, NULL);
    if (!pb) {
        err = -1;
        fprintf(stderr, "Failed to create ring buffer\n");
        hello_buffer_config_bpf__destroy(skel);
        return 1;
    }

    while (true) {
        err = perf_buffer__poll(pb, 100 /* timeout, ms */);
        // Ctrl-C gives -EINTR
        if (err == -EINTR) {
            err = 0;
            break;
        }
        if (err < 0) {
            printf("Error polling perf buffer: %d\n", err);
            break;
        }
    }

    perf_buffer__free(pb);
    hello_buffer_config_bpf__destroy(skel);
    return -err;
}
