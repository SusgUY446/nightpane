@echo off


if exist build rd build /s /q
if exist .xmake rd .xmake /s /q
if exist os.bin del os.bin
if exist oskrnl.elf del oskrnl.elf