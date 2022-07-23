CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
OC = aarch64-linux-gnu-objcopy

TARGET_CPU = cortex-a53

boot: boot.S
	$(AS) -mcpu=$(TARGET_CPU) -c $@.S -o $@.o

kernel: kmew_kernel.c
	$(CC) -mcpu=$(TARGET_CPU) -c kmew_kernel.c -o kernel.o

link:
	$(CC) -T linker.ld -o kmew_os.elf -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc 
	$(OC) kmew_os.elf -O binary kernel.img
