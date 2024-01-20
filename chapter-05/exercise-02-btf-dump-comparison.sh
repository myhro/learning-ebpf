#!/bin/bash

set -eu

FILE=$(bpftool btf dump file hello-buffer-config.bpf.o)
PROG=$(sudo bpftool btf dump prog name hello)

diff -u <(echo "$FILE") <(echo "$PROG")
