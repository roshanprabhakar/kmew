## REMOVED DEBUG SYMBOLS ##

CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-gcc
OC = aarch64-linux-gnu-objcopy

TARGET_CPU = cortex-a53

SRC_ASM := $(shell find src/ -name *.S)
SRC_C := $(shell find src/ -name *.c)

OBJ_ASM := $(patsubst src/%.S, build/%.o, $(SRC_ASM))
OBJ_C := $(patsubst src/%.c, build/%.o, $(SRC_C))

OPS_C := -Wall -nostdlib -nostartfiles -ffreestanding -DPRINTF_DISABLE_SUPPORT_FLOAT -mgeneral-regs-only -fno-stack-protector -mcpu=$(TARGET_CPU) -g
OPS_ASM := -mcpu=$(TARGET_CPU) -g

all: $(OBJ_ASM) $(OBJ_C)
	$(CC) -T src/linker.ld -o build/kmew_os.elf -ffreestanding -nostdlib $(OBJ_ASM) $(OBJ_C) -lgcc 
	$(OC) build/kmew_os.elf -O binary build/kmew_os.img


$(OBJ_ASM): build/%.o : src/%.S
	mkdir -p $(dir $@) && \
	$(AS) $(OPS_ASM) -c $(patsubst build/%.o, src/%.S, $@) -o $@ 

$(OBJ_C): build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	$(CC) $(OPS_C) -c $(patsubst build/%.o, src/%.c, $@) -o $@ 

clean:
	rm -rf build

dump:
	objdump -d build/kmew_os.elf
