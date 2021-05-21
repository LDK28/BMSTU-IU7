SD1 SEGMENT para common 'DATA'
	C1 LABEL byte
	ORG 1h
	C2 LABEL byte
SD1 ENDS

CSEG SEGMENT para 'CODE'
	ASSUME CS:CSEG, DS:SD1
main:
	mov ax, SD1
	mov ds, ax
	mov ah, 2
	mov dl, C1
	int 21h
	mov dl, C2
	int 21h
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main