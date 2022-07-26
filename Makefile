## REMOVED DEBUG SYMBOLS ##

CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
OC = aarch64-linux-gnu-objcopy

TARGET_CPU = cortex-a53

SRC_ASM := $(shell find src/ -name *.asm)
SRC_C := $(shell find src/ -name *.c)

OBJ_ASM := $(patsubst src/%.asm, build/%.o, $(SRC_ASM))
OBJ_C := $(patsubst src/%.c, build/%.o, $(SRC_C))


all: $(OBJ_ASM) $(OBJ_C)
	$(CC) -T src/linker.ld -o build/kmew_os.elf -ffreestanding -nostdlib $(OBJ_ASM) $(OBJ_C) -lgcc 
	$(OC) build/kmew_os.elf -O binary build/kmew_os.img


$(OBJ_ASM): build/%.o : src/%.asm
	mkdir -p $(dir $@) && \
	$(AS) -mcpu=$(TARGET_CPU) -c $(patsubst build/%.o, src/%.asm, $@) -o $@ 

$(OBJ_C): build/%.o : src/%.c
	mkdir -p $(dir $@) && \
	$(CC) -fno-stack-protector -mcpu=$(TARGET_CPU) -c $(patsubst build/%.o, src/%.c, $@) -o $@ 

clean:
	rm -rf build

