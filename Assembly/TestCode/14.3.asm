assume cs:code

code segment
start:  mov ax, 2
        shl ax, 1
        mov dx, ax
        mov ax, 2
        mov cl, 3
        shl ax, cl
        add ax, dx
code ends
end start