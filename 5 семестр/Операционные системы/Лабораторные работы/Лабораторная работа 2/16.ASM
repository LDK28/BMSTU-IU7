.586                    ; Разрешение всех команд Pentium
;.386P

; Структура для описания дескрипторов сегментов
descr   struc           ; Начало объявления структуры
    lim     dw 0            ; Граница (биты 0...15)
    base_l  dw 0            ; База, биты 0...15
    base_m  db 0            ; База, биты 1...23
    attr_1  db 0            ; Байт атрибутов 1
    attr_2  db 0            ; Границы (биты 16...19) и атрибуты 2
    base_h  db 0            ; База, биты 24...31
descr   ends            ; Конец объявления структуры

; Сегмент данных
; use16 - использование 16-битных адресов по умолчанию.
data    segment use16   ; 16-разрядный сегмент
5
    ; Таблица глобальных дескрипторов GDT
    gdt_null    descr <0,0,0,0,0,0> ; Селектор 0, нулевой дескриптор
    gdt_data    descr <data_size-1,0,0,92h,0,0> ; Селектор 8, сегмент данных
    gdt_code    descr <code_size-1,0,0,98h,0,0> ; Селектор 16, сегмент команд
    gdt_stack   descr <255,0,0,92h,0,0>         ; Селектор 24, сегмент стека
    gdt_screen  descr <3999,8000h,0Bh,92h,0,0>  ; Селектор 32, видеопамять
    gdt_datacheck descr<0FFFFh,0,0,92h,11001111b,0>
    gdt_size=$-gdt_null                         ; Размер GDT

    ; Различные данные программы
    pdescr  df  0                               ; Псевдодескриптор для команды lgdt

    realmode     db  'REAL MODE'
    realmode_len=$-realmode
    protectmode  db  'PROTECTED MODE'
    protectmode_len=$-protectmode

    color=1Fh
    col=26
    row=13

    data_size=$-gdt_null                        ; Размер сегиента данных
data ends


text segment 'code' use16
    assume  cs:text, ds:data
    main    proc
        xor eax, eax                            ; Очистим eах
        mov eax, data                           ; Загрузим в ds сегиентный
        mov ds, eax                             ; адрес сегмента данных
        mov eax, 0B800h
        mov es, eax

        mov di, row * 160 + col * 2
        mov bx, offset realmode
        mov cx, realmode_len
        mov ah, color

        loop_01: 
            mov al, byte ptr [bx]
            inc bx
            stosw
        loop loop_01

        ; Загрузка линейного адреса сегмента данных в GDT
        xor eax, eax
        mov ax, data
        ; Вычислим 32-битовый линейный адрес сегмента данных и загрузим его
        ; в дескриптор сегмента данных в таблице глобалных дескрипторов GDT
        shl eax, 4                              ; eax=линейный базовый адрес
        mov ebp, eax                            ; Сохраняем его в ebp для будущего
        mov bx, offset gdt_data                 ; bx=смещение дескриптора
        mov (descr ptr [bx]).base_l, ax         ; Загрузим младшую часть базы
        shr eax, 16                             ; Старшую половину eax в ax
        mov (descr ptr [bx]).base_m, al         ; Загрузим среднюю часть базы

        ; Вычислим и загрузим в GDT линейный адрес сегмента команд
        xor eax, eax                            ; Очистим eах
        mov ax, cs                              ; Сегментный адрес сегмента команд
        shl eax, 4
        mov bx, offset gdt_code
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al

        ; Вычислим и загрузим в GDT линейный адрес сегмента стека
        xor eax, eax                            ; Очистим eах
        mov ax, ss                              ; Сегментный адрес сегмента стека
        shl eax, 4
        mov bx, offset gdt_stack
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al

        ; Подготовим псевдодескриптор pdescr и зашрузим регистр GDTR
        mov dword ptr pdescr + 2, ebp           ; База GDT
        mov word ptr pdescr, gdt_size - 1       ; Граница GDT
        lgdt pdescr                             ; Загрузим регистр GDTR

        cli

        ; Переходим в защищенный режим
        mov eax, cr0                            ; Получим содержимое регистра cr0
        or  eax, 1                              ; Установим бит защищённого режима
        mov cr0, eax                            ; Запишем назад в cr0

        ; Искусственно сконструированная команда дальнего перехода для смены CS:IP
        db  0EAh                                ; Код команды far jmp
        dw  offset continue                     ; Смещение
        dw  16                                  ; Селектор сегмента кода

    continue:
        ; Заносим в ds селектор сегмента данных
        mov ax, 8                               ; Селектор сегмента данных
        mov ds, ax

        ; Заносим в ss селектор сегмента стека
        mov ax, 24                              ; Селектор сегмента стека
        mov ss, ax

        ; Заносим в es селектор сегмента видеопамяти
        mov ax, 32                              ; Селектор сегмента видеобуфера
        mov es, ax

        ; Заносим в GS селектор сегмента размера 4ГБ
        mov ax, 40
        mov gs, ax
        
        ; Вывод сообщения о переходе
        mov di, (row + 1) * 160 + col * 2
        mov bx, offset protectmode
        mov cx, protectmode_len
        mov ah, color

        loop_02:
            mov al, byte ptr [bx]
            inc bx
            stosw
        loop loop_02


        mov gdt_data.limit, 0FFFFh
        mov gdt_code.limit, 0FFFFh
        mov gdt_stack.limit, 0FFFFh
        mov gdt_screen.limit, 0FFFFh

        push ds
        pop  ds
        push es
        pop  es
        push ss
        pop  ss

    ; Загрузка селектора в регистр CS и модификация теневого регистра
        db  0EAh
        dw  offset go
        dw  16

    ; Переключение режима процессора
    go:
        mov eax, cr0
        and eax, 0FFFFFFFEh
        mov cr0, eax
        db  0EAh
        dw  offset return
        dw  text

    return:
        ; Восстановим вычислительную среду реального режима
        mov ax, data                                ; Сделаем адресуемыми данные
        mov ds, ax
        mov ax, stk                                 ; Сделаем адресуемым стек
        mov ss, ax

        sti                                         ; Разрешим аппаратные прерывания

        ; Вывод сообщения о возврате
        mov di, (row + 2) * 160 + col * 2
        mov bx, offset realmode
        mov cx, realmode_len
        mov ah, color

        loop_03:
            mov al, byte ptr [bx]
            inc bx
            stosw
        loop loop_03

        mov ax, 4C00h                               ; Завершим программу обычным образом
        int 21h

    main    endp
    code_size=$-main                                ; Размер сегмента команд
text    ends

; Сегмент стека
stk segment stack 'stack'
    db  256 dup('^')
stk ends
end main