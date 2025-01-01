section .bss
    align 16
stack_bottom:
    resb 655360      
stack_top:

section .data
    message db "Loading System......", 10, 0

section .text
    global KiEntry
    extern KiMain
    extern KiSetupPaging
    extern KiTerminalPrint
    extern KiSetupGDT
    extern KiSetupIDT
KiEntry:
    ;call KiSetupPaging 
    mov rsp, stack_top    
    cli
    call KiSetupGDT
    call KiSetupIDT
    sti
    call KiMain
    cli
.halt:
    hlt
    jmp .halt