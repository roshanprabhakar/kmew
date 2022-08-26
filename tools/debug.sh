#!/usr/bin/env bash

cd "$(dirname "$0")"

pushd ..
gdb-multiarch ../build/kmew_os.elf -x gdbsetup.gdb
popd
