#!/bin/bash

make exercise-01-invalid-offset.bpf.o
sudo bpftool prog load exercise-01-invalid-offset.bpf.o /sys/fs/bpf/exercise-01-invalid-offset
