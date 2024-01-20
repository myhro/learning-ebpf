%.bpf.o: %.bpf.c
	clang -target bpf -D __TARGET_ARCH_x86 -I /usr/include/x86_64-linux-gnu/ -g -O2 -c $< -o $@
	llvm-strip-14 -g $@

clean:
	rm -f *.o vmlinux.h

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
