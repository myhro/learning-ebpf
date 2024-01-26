build:
	go build

clean:
	rm -f *.o *_bpfeb.go *_bpfel.go hello

dump:
	llvm-objdump-14 -S *.o

generate:
	go generate

list:
	sudo bpftool prog list

run:
	sudo ./hello

strace:
	sudo strace -e bpf ./hello

trace:
	sudo cat /sys/kernel/debug/tracing/trace_pipe
