PREFIX ?= i686-elf-
CC := $(PREFIX)gcc
LD := $(PREFIX)ld
AS := nasm

CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -fno-pie -fno-stack-protector
LDFLAGS := -m elf_i386 -T linker.ld

BUILD := build
ISO := $(BUILD)/kadados.iso
KERNEL := $(BUILD)/kadados.bin

OBJS := $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/console.o $(BUILD)/keyboard.o $(BUILD)/fs.o $(BUILD)/shell.o $(BUILD)/string.o

.PHONY: all iso run clean

all: iso

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/boot.o: boot.asm | $(BUILD)
	nasm -f elf32 $< -o $@

$(BUILD)/%.o: kernel/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

iso: $(KERNEL) grub.cfg
	mkdir -p $(BUILD)/isodir/boot/grub
	cp $(KERNEL) $(BUILD)/isodir/boot/kadados.bin
	cp grub.cfg $(BUILD)/isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) $(BUILD)/isodir

run: iso
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf $(BUILD)
