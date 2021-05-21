section .text
global _strcopy

_strcopy:
    pushf
    mov rcx, rdx

    ; сброс флагов
    cld
    cmp rsi, rdi
    je exit
    cmp rsi, rdi
    jg copy

    mov rax, rsi
    sub rax, rdi
    cmp rax, rcx
    jge copy

    add rdi, rcx
    dec rdi
    add rsi, rcx
    dec rsi
    std
    jmp copy
    
copy:
    rep movsb   ; movsb записывает в rdi из rsi по байту, а repne будет поворять ровно rcx раз
    
exit:
    popf
    ret
