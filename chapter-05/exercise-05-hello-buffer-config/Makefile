.PHONY: hello-buffer-config

%.bpf.o: %.bpf.c
	clang -target bpf -D __TARGET_ARCH_x86 -I /usr/include/x86_64-linux-gnu/ -g -O2 -c $< -o $@
	llvm-strip-14 -g $@

%.skel.h: %.bpf.o
	bpftool gen skeleton $< > $@

clean:
	rm -f *.o *.skel.h hello-buffer-config vmlinux.h

hello-buffer-config: hello-buffer-config.skel.h
	gcc $@.c -o $@ -lbpf

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
