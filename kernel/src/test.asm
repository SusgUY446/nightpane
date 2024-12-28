section .data
    message db "Hi Assembly", 10, 0


section .text
    global KiTestAsmCLinkage
    extern KiTerminalPrint

KiTestAsmCLinkage:
    push rbp             
    mov rbp, rsp   
    mov rax, fs:[0x0]     ; Read from the FS segment
    mov rax, gs:[0x0]     ; Read from the GS segment
    mov rsp, rbp          
    pop rbp   
    ret