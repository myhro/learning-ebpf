%.bpf.o: %.bpf.c
	clang -target bpf -D __TARGET_ARCH_x86 -I /usr/include/x86_64-linux-gnu/ -g -O2 -c $< -o $@
	llvm-strip-14 -g $@

attach:
	sudo bpftool net attach xdp name ping dev enp5s0

clean:
	rm -f *.o vmlinux.h

detach:
	sudo bpftool net detach xdp dev enp5s0

list:
	sudo bpftool prog list

load:
	sudo bpftool prog load ping.bpf.o /sys/fs/bpf/ping

trace:
	sudo cat /sys/kernel/debug/tracing/trace_pipe

unload:
	sudo rm /sys/fs/bpf/ping

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
