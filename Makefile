CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
OC = aarch64-linux-gnu-objcopy

TARGET_CPU = cortex-a53

SRC_ASM := $(shell find src/ -name *.asm)
OBJ_ASM := $(patsubst src/%.asm, build/%.o, $(SRC_ASM))

all: $(OBJ_ASM)
	$(CC) -T linker.ld -o kmew_os.elf -ffreestanding -O2 -nostdlib $(OBJ_ASM) -lgcc
	$(OC) kmew_os.elf -O binary kernel.img

$(OBJ_ASM): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	$(AS) -mcpu=$(TARGET_CPU) -c $(patsubst build/%.o, src/%.asm, $@) -o $@

clean:
	rm -rf build
