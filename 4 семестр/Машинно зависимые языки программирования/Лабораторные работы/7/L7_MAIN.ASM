.MODEL TINY
.CODE
.386

ORG 100h 

MAIN:
    TIME DB 0
    MOV AH, 02h
    INT 1Ah
    MOV TIME, DH
	
    SPEED DB 01Fh
    OLD_08H DD ?
    IS_INIT DB 'I'

    JMP INIT

MY_INT_08h PROC NEAR
    PUSHA
    PUSHF
    PUSH ES
    PUSH DS

    MOV AH, 02h
    INT 1Ah

    CMP DH, TIME
    MOV TIME, DH
    JE QUIT

    MOV AL, 0F3h
    OUT 60h, AL
    MOV AL, SPEED
    OUT 60h, AL

    DEC SPEED
    JNZ QUIT
    MOV SPEED, 01fh

    QUIT:
        POP DS
	    POP ES
	    POPF
	    POPA
        JMP CS:OLD_08H
MY_INT_08h ENDP

INIT:
    MOV AX, 3508h
    INT 21H

    CMP ES:IS_INIT, 'I'
    JE UNINSTALL

    MOV WORD PTR OLD_08H, BX
    MOV WORD PTR OLD_08H + 2, ES

    MOV AX, 2508h
    MOV DX, OFFSET MY_INT_08h
    INT 21H

    MOV DX, OFFSET INIT
    INT 27H

UNINSTALL:
    PUSH ES
    PUSH DS

    ;Установка старого вектора прерывания
    MOV DX, WORD PTR ES:OLD_08H
    MOV DS, WORD PTR ES:OLD_08H + 2
    MOV AX, 2508h 
    INT 21H
  
    POP DS
    POP ES
    MOV AH, 49h
    INT 21h

    MOV AX, 4C00h
    INT 21h
    
END MAIN