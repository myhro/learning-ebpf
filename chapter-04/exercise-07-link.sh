#!/bin/bash

set -eu

ID="$(sudo bpftool link list | head -1 | cut -d ':' -f 1)"
sudo bpftool link pin id "$ID" /sys/fs/bpf/mylink
