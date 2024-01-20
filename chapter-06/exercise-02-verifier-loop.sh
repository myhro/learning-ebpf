#!/bin/bash

make exercise-02-verifier-loop.bpf.o
sudo bpftool prog load -d exercise-02-verifier-loop.bpf.o /sys/fs/bpf/exercise-02-verifier-loop
sleep 1
sudo rm /sys/fs/bpf/exercise-02-verifier-loop
