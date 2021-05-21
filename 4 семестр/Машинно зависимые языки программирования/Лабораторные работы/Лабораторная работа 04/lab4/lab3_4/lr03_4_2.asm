EXTRN X: byte
PUBLIC exit

SD2 SEGMENT para 'DATA'
	Y db 'Y'
SD2 ENDS

SC2 SEGMENT para public 'CODE'
	assume CS:SC2, DS:SD2
exit:
	mov ax, seg X
	mov es, ax
	mov bh, es:X

	mov ax, SD2
	mov ds, ax

	xchg ah, Y
	xchg ah, ES:X
	xchg ah, Y	

	mov ah, 2
	mov dl, Y
	int 21h	
	
	mov ax, 4c00h
	int 21h
SC2 ENDS
END