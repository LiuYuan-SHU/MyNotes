assume cs:code, ds:data, ss:stack

stack segment
    db 4 dup('.')
stack ends

data segment
    string          db  'welcome to masm!'  ; 16 Byte
    green           db  00000010B           ; 1 Byte
    g_r             db  00100100B           ; 1 Byte
    w_b             db  01110001B           ; 1 Byte
    place_holder    db  01110000B           ; 1 Byte
data ends

code segment
    start:  
        ; clear screen
        mov ah, 15
        int 10h
        mov ah, 0
        int 10h

        ; init ds reg
        mov ax, data
        mov ds, ax
        ; init ss/sp reg
        mov ax, stack
        mov ss, ax
        mov sp, 4
        ; init es reg
        mov ax, 0B800H
        mov es, ax

    write_char:
            ; write characters into lines

            ; in C code:
            ; for (int line = 0; line <= 0x140; line += 160)
			; {
				; const int start = 0x4A;
				; for (int index = 0; index < 16; index++)
				; {
					; (B8000H + line + start + index * 2) = (string + index);	
				; }
			; }
            mov cx, 0	
        write_row:
            push cx
            mov si, cx

            mov cx, 0
            write_col:
                ; (B8000H + line + start + index * 2) = (string + index);	
                ;  es        si    idata      bx               dx

                ; string + index
                mov bx, cx
                mov dl, ds:[bx] ; store char in dl
                ; set color in dh
                mov dh, 10001001B
                add dh, cl
                again:
                cmp dh, 10001111B
                jle continue
                sub dh, 0110B
                jmp again

                continue:
                ; index * 2
                mov ax, cx
                mov bl, 2
                mul bl      ; store result in ax
                mov bx, ax  ; store result in bx

                ; move character to memory
                mov es:[bx + si + 4AH], dx

                ; check and loop
                inc cx
                cmp cx, 16
                jl write_col

            ; check and loop
            pop cx
            add cx, 160D
            ; cmp cx, 140H
            cmp cx, 0F9FH
            jle write_row

    exit:
        mov ax, 4C00H
        int 21H
code ends
end start
