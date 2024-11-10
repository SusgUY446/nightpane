section .text
    global KiEnablePaging



KiEnablePaging:
    push rbp             
    mov rbp, rsp
    mov rax, 0x00000020
    mov cr4, rax

    mov rax, cr0
    or rax, 0x80000000
    mov cr0, rax
    mov rsp, rbp          
    pop rbp       
    ret