#!/usr/bin/env bash
cd "$(dirname "$0")"

pushd ..
qemu-system-aarch64 -S -M raspi3b -kernel build/kmew_os.img -monitor stdio
popd
