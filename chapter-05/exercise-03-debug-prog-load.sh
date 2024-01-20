#!/bin/bash

sudo bpftool -d prog load hello-buffer-config.bpf.o /sys/fs/bpf/hello
sleep 1  # Avoid 'Error: failed to pin program ksyscall/execve' if unpinning it immediately
sudo rm /sys/fs/bpf/hello
