@echo off


if "%1"=="debug" (
    qemu-system-x86_64 -drive file=image\image.vhd,format=vpc -bios ovmf\ovmf.fd -m 512M -device virtio-gpu-pci -display sdl -boot d -d int,cpu_reset -s -S 

) else (
    qemu-system-x86_64 -drive file=image\image.vhd,format=vpc -bios ovmf\ovmf.fd -m 512M -device virtio-gpu-pci -display sdl
)   
