PUBLIC newline
PUBLIC print_matrix
PUBLIC space

EXTRN n: byte
EXTRN m: byte
EXTRN matrix: byte


SEGDATA SEGMENT PARA COMMON 'DATA'
SEGDATA ENDS


SEGCODE SEGMENT PARA PUBLIC 'CODE'
    assume CS:SEGCODE, DS:SEGDATA
newline proc near
    mov ah, 2
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    ret
newline endp

print_matrix proc near
    mov ah, 2
    mov bl, m
    mov si, 0
    
    print_col:
        mov cl, n
        sub cl, dh
        print_row:
            mov dl, byte ptr[matrix + si]
            inc si
            int 21h

            mov dl, " "
            int 21h
            loop print_row

        call newline

        mov cl, bl
        dec bl

        mov al, 1
        mul dh
        add si, ax
        
        mov ah, 2
        loop print_col

    ret

print_matrix endp

space proc near
    mov ah, 2
    mov dl, " "
    int 21h

    ret
space endp

SEGCODE ENDS
END