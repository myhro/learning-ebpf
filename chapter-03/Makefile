%.bpf.o: %.bpf.c
	clang -target bpf -I /usr/include/x86_64-linux-gnu/ -g -O2 -c $< -o $@

attach:
	sudo bpftool net attach xdp name hello dev enp5s0

clean:
	rm -f *.o

detach:
	sudo bpftool net detach xdp dev enp5s0

dump:
	file hello.bpf.o
	llvm-objdump -S hello.bpf.o
	sudo bpftool prog dump xlated name hello

dump-map:
	sudo bpftool map dump name hello.bss
	sudo bpftool map dump name hello.rodata

list:
	sudo bpftool prog list

list-map:
	sudo bpftool map list

list-net:
	sudo bpftool net list

load:
	sudo bpftool prog load hello.bpf.o /sys/fs/bpf/hello

show:
	sudo bpftool prog show name hello

trace:
	sudo cat /sys/kernel/debug/tracing/trace_pipe

unload:
	sudo rm /sys/fs/bpf/hello
