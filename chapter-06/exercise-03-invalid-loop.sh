#!/bin/bash

make exercise-03-invalid-loop.bpf.o
time sudo bpftool prog load exercise-03-invalid-loop.bpf.o /sys/fs/bpf/exercise-03-invalid-loop
