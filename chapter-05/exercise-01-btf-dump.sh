#!/bin/bash

set -x

sudo bpftool btf dump prog name hello

sudo bpftool btf dump map name my_config
