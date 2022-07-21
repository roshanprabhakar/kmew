#!/usr/bin/env bash

qemu-system-aarch64 \
	-machine raspi2b \
	-cpu cortex-a53 \
	-smp cores=1,threads=1 \
	-m 128 \
	-drive format=raw,media=cdrom,file=nos.iso \
	-serial stdio \
	-usb \
	-vga std
