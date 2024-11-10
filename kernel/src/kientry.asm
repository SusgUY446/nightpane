section .bss
    align 16
stack_bottom:
    resb 65536       
stack_top:

section .data

section .text
    global KiEntry
    extern KiMain
    extern KiSetupPaging
    extern KiTestAsmCLinkage

KiEntry:
    
    call KiSetupPaging 
    mov rsp, stack_top     
    call KiMain
    cli
.halt:
    hlt
    jmp .halt