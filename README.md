# KadadOS

KadadOS is a from-scratch x86 operating system project.

## Current target

A small standalone OS with:
- x86 BIOS boot
- protected-mode kernel
- VGA text console
- PS/2 keyboard input
- in-memory filesystem
- interactive Kadad shell
- `ls`, `dir`, `mkdir`, `rm`, `rmdir`, `cd`, `pwd`, `echo`, `clear`, `help`
- blinking shell cursor
- VPS/headless architecture planned around an SSH userspace service

Shell prompt:

```
kavan@Kadad--kavan /home/kavan/ >_
```

## Build

Requirements: NASM, GCC cross compiler (`i686-elf-gcc`), GNU ld, GRUB utilities, xorriso and QEMU.

```sh
make
make run
```

This repository does not require a VPS for development. Build and test the OS locally, then deploy the finished image to a VPS.
