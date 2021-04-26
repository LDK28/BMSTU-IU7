STACK  SEGMENT PARA STACK 'STACK'
        DB      10h DUP (?)
STACK  ENDS

CodeOut SEGMENT PARA 'CODE'
        ASSUME CS:CodeOut
        PrintSymbol:
                MOV     DX, 10
                MOV 	AH, 02h
                INT     21h

                MOV     DX, BX
                ADD     DX, 32
                MOV 	AH, 02h
                INT     21h

                MOV     AH, 4Ch
                INT     21h
CodeOut ENDS

CodeIn  SEGMENT PARA 'CODE'
        ASSUME  CS:CodeIn, SS:STACK

        GetSymbol:
                MOV     AH, 01h
                INT	21h
                MOV     BX, AX

                CALL    CodeOut:PrintSymbol
                ;JMP FAR PTR PrintSymbol

CodeIn  ENDS
        END     GetSymbol

