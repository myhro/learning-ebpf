#!/bin/bash

sudo strace -e bpf bpftool map dump name config
