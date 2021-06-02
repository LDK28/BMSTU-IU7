format PE GUI 4.0
entry start

include 'win32ax.inc'

ID_A               = 101
ID_B               = 102
ID_ICONINFORMATION = 200
DIALOG_TEMPLATE    = 22


section '.text' code readable executable
    message_res db 'Result: '
    db 0
    flags dd MB_OK

    start:
        invoke  GetModuleHandle,0
        invoke  DialogBoxParam,eax,DIALOG_TEMPLATE,HWND_DESKTOP,DialogProc,0
        or      eax,eax
        jz      exit

        call sum
        invoke  MessageBox,HWND_DESKTOP,b_num,message_res,[flags]

        jmp start
    exit:
        invoke  ExitProcess,0

    sum:
        mov     al, [b_num]
        mov     bl, [a_num]
        sub     al, '0'
        sub     bl, '0'
        add     al, bl
        add     al, '0'
        cmp     al, '9'
        jg      .sum_two
            mov     [b_num], al
            mov     [b_num + 1], 0
            jmp     .sum_finish
        .sum_two:
            mov     [b_num], '1'
            sub     al, 10
            mov     [b_num + 1], al
            mov     [b_num + 2], 0
        .sum_finish:
        ret

proc DialogProc hwnddlg,msg,wparam,lparam
        push    ebx esi edi
        cmp     [msg],WM_COMMAND
        je      .wmcommand
        cmp     [msg],WM_CLOSE
        je      .wmclose
        xor     eax,eax
        jmp     .finish
    .wmcommand:
        cmp     [wparam],BN_CLICKED shl 16 + IDOK
        jne     .processed
        invoke  GetDlgItemText,[hwnddlg],ID_A,a_num,2h
        invoke  GetDlgItemText,[hwnddlg],ID_B,b_num,2h
        invoke  EndDialog,[hwnddlg],1
        jmp     .processed
    .wmclose:
        invoke  EndDialog,[hwnddlg],0
    .processed:
        mov     eax,1
    .finish:
        pop     edi esi ebx
        ret
endp

section '.bss' readable writeable
    a_num rb 4h                 ; Reserve bytes
    b_num rb 4h

section '.idata' import data readable writeable

    library kernel,'KERNEL32.DLL',\
        user,'USER32.DLL'

    import kernel,\
        GetModuleHandle,'GetModuleHandleA',\
        ExitProcess,'ExitProcess'

    import user,\
        DialogBoxParam,'DialogBoxParamA',\
        GetDlgItemText,'GetDlgItemTextA',\
        MessageBox,'MessageBoxA',\
        EndDialog,'EndDialog'

section '.rsrc' resource data readable

    directory RT_DIALOG,dialogs

    resource dialogs,\
        DIALOG_TEMPLATE,LANG_ENGLISH+SUBLANG_DEFAULT,demonstration

    dialog demonstration,'Counter',70,70,190,105,WS_CAPTION+WS_POPUP+WS_SYSMENU+DS_MODALFRAME
        dialogitem 'STATIC','&A:',-1,10,10,70,8,WS_VISIBLE
        dialogitem 'EDIT','',ID_A,10,20,170,13,WS_VISIBLE+WS_BORDER+WS_TABSTOP
        dialogitem 'STATIC','&B:',-1,10,40,70,8,WS_VISIBLE
        dialogitem 'EDIT','',ID_B,10,50,170,13,WS_VISIBLE+WS_BORDER+WS_TABSTOP+ES_AUTOHSCROLL
        dialogitem 'BUTTON','&SUM',IDOK,10,70,170,20,WS_VISIBLE

    enddialog
