@echo off



qemu-system-x86_64 -drive file=image\image.vhd,format=vpc -bios ovmf\ovmf.fd -m 512M -device virtio-gpu-pci -display sdl
