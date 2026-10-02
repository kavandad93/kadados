#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/build"
RAW="$BUILD/kadados.raw"
MOUNT="$BUILD/raw-mount"
SIZE_MB="${KADADOS_RAW_SIZE_MB:-64}"

mkdir -p "$BUILD"
rm -f "$RAW"
truncate -s "${SIZE_MB}M" "$RAW"

mkfs.ext2 -F "$RAW" >/dev/null

rm -rf "$MOUNT"
mkdir -p "$MOUNT"
sudo mount -o loop "$RAW" "$MOUNT"
trap 'sudo umount "$MOUNT" 2>/dev/null || true; rm -rf "$MOUNT"' EXIT

sudo mkdir -p "$MOUNT/boot/grub"
sudo cp "$BUILD/kadados.bin" "$MOUNT/boot/kadados.bin"
sudo cp "$ROOT/grub.cfg" "$MOUNT/boot/grub/grub.cfg"

sudo grub-install \
  --target=i386-pc \
  --boot-directory="$MOUNT/boot" \
  --modules="normal multiboot biosdisk ext2" \
  --no-floppy \
  "$RAW" >/dev/null

sync
echo "RAW image created: $RAW"
