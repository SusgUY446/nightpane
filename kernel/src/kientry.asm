section .bss
    align 16
stack_bottom:
    resb 65536       
stack_top:

section .data
    message db "Hello World", 10, 0

section .text
    global KiEntry
    extern KiMain
    extern KiSetupPaging
    extern KiTerminalPrint
    extern KiSetupGDT
KiEntry:
    ;call KiSetupPaging 
    mov rsp, stack_top    
    call KiSetupGDT
    call KiMain
    cli
.halt:
    hlt
    jmp .halt