#!/bin/bash

sudo strace -e bpf ./hello-ring-buffer-config.py 2>&1 | grep hello
