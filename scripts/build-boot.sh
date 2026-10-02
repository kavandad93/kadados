#!/bin/sh
set -eu

mkdir -p build
nasm -f bin kernel/boot.asm -o build/kadados-boot.bin

echo "Built build/kadados-boot.bin"
