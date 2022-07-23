CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as

TARGET_CPU = cortex-a53

boot: boot.S
	$(AS) -mcpu=$(TARGET_CPU) -c $@.S -o $@.o
