section .data
    message db "Hi Assembly", 10, 0


section .text
    global KiTestAsmCLinkage
    extern KiTerminalPrint

KiTestAsmCLinkage:
    push rbp             
    mov rbp, rsp   
    mov rdi, message
    call KiTerminalPrint
    mov rsp, rbp          
    pop rbp   
    ret