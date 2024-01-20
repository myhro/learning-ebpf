#!/bin/bash

set -eux

FILE="5.3.7-301.fc31.x86_64.btf"
curl -L "https://github.com/aquasecurity/btfhub-archive/raw/main/fedora/31/x86_64/${FILE}.tar.xz" | tar Jx
bpftool btf dump file $FILE format c > vmlinux.h
rm -f $FILE

# Avoid "error: use of undeclared identifier 'BPF_F_CURRENT_CPU'"
echo "int BPF_F_CURRENT_CPU = 1;" >> vmlinux.h
