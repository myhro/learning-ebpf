#!/bin/bash

sudo strace -e bpf ../chapter-05/hello-buffer-config 2>&1 | grep BPF_LINK_CREATE
