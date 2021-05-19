PUBLIC delete_even

EXTRN n: byte
EXTRN m: byte
EXTRN matrix: byte

SEGCODE SEGMENT PARA PUBLIC 'CODE'
    assume CS:SEGCODE

delete_even proc near
    mov si, 0               ;счётчитк столбцов
    mov dh, 0
    lbl_col:                ;цикл по столбцам
        jmp check_column

        ret1:

        inc si              ;переход к следующему столбцу
        
        mov al, 1
        mul n
        cmp si, ax
        jne lbl_col
    
    ret

check_column:               ;проверка элементов столбца
    xor dl, dl               ;счётчитк строк
    continue1:
        call get_index

        ;проверка на четность
        mov ah, matrix[bx]
        test ah, 1
        jnz ret1                ;если нечетный - переходим к следующему столбцу(возвращаемся)
        
        add dl, 1               ;переход к следующей строке
        cmp dl, m
        jne continue1
        je reset

reset:                      ;обнуление элементов столбца
    
    xor dl, dl
    continue2:

        call get_index

        call swap

        inc dl
        cmp dl, m
        jne continue2
        je made
made:
    inc dh
    jmp ret1 

get_index:
    ;вычисление индекса элемента
    mov al, dl
    mul n
    add ax, si
    mov bx, ax              ;ax нельзя использовать в качестве индекса
    ret

swap:
    mov al, 1
    mul n
    dec ax
    sub ax, si
    mov cx, ax
    cycle:
        mov ah, matrix[bx + 1]
        mov matrix[bx], ah
        
        inc bx
        loop cycle
    

    ret

delete_even endp

SEGCODE ENDS
END