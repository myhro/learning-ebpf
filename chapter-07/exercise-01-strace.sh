#!/bin/bash

sudo strace -e bpf ./hello 2>&1 | grep BPF_PROG_LOAD
