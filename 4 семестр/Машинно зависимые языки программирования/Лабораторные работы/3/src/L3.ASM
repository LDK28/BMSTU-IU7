StkSeg  SEGMENT PARA STACK 'STACK'
        DB      200h DUP (?)
StkSeg  ENDS
;
DataS   SEGMENT WORD 'DATA'
HelloMessage    DB   13                 ;курсор поместить в нач. строки
                DB   10                 ;перевести курсор на нов. строку
                DB   '0'                ;текст сообщения
                DB   '$'                ;ограничитель для функции DOS
DataS   ENDS
;
Code    SEGMENT WORD 'CODE'
        ASSUME  CS:Code, DS:DataS
DispMsg:
        MOV   AX,DataS                  ;загрузка в AX адреса сегмента данных
        MOV   DS,AX                     ;установка DS

        MOV   AH,2                      ;АН=09h выдать на дисплей строку
        
        MOV   CX,3
        QWERTY:
                MOV   DX,'0'
                MOV   BX,CX
                MOV   CX,3
                PRINT:
                        ADD   DX,1
                        INT   21h                       
                        loop  PRINT
                MOV   DX, 10
                INT   21h
                MOV   CX,BX 
                loop QWERTY
        
        MOV   AH,7                      ;АН=07h ввести символ без эха
        INT   21h                       ;вызов  функции DOS
        MOV   AH,4Ch                    ;АН=4Ch завершить процесс
        INT   21h                       ;вызов  функции DOS
Code    ENDS
        END   DispMsg