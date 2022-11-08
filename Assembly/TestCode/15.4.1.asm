; 依次显示a ~ z

assume cs:code
code segment
start:  mov ax, 0b800h
        mov es, ax
        mov ah, 'a'
    s:  mov es:[160 * 12 + 40 * 2], ah
        inc ah
        cmp ah, 'z'
        jna s
        mov ax, 4C00H
        int 21H
code ends
end start