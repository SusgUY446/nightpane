section .bss
    align 16
stack_bottom:
    resb 65536       
stack_top:

section .data
    loadmessage db "Loading RontoCores Kernel....", 10, 10, 0

section .text
    global KiEntry
    extern KiMain

KiEntry:
    mov rsp, stack_top     
    call KiMain
    cli

.halt:
    hlt