#!/bin/bash

sudo strace -e bpf ./exercise-05-hello-buffer-config.py 2>&1 | grep raw_tracepoint
