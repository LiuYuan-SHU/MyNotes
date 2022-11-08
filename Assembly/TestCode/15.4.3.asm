; 中断例程

assume cs:code

stack segment
    db 128 dup(0)
stack ends

data segment
    dw 0, 0
data ends

code segment
start:  mov ax, stack
        mov ss, ax
        mov sp, 128

        mov ax, data
        mov ds, ax

        mov ax, 0
        mov es, ax

        push es:[9 * 4]
        pop ds:[0]
        push es:[9 * 4 + 2]
        pop ds:[2]              ; 将原来的int 9中断例程的入口地址保存在ds:0，ds:2中

        mov word ptr es:[9 * 4], offset int9
        mov es:[9 * 4 + 2], cs  ; 在中断向量表中设置新的int9中断例程的入口地址
        
        mov ax, 0b800h
        mov es, ax
        mov ah, 'a'
    s:  mov es:[160 * 12 + 40 * 2], ah
        call delay
        inc ah
        cmp ah, 'z'
        jna s

        mov ax, 0
        mov es, ax

        push ds:[0]
        pop es:[9 * 4]
        push ds:[2]
        pop es:[9 * 4 + 2]

        mov ax, 4C00H
        int 21H

delay:  push ax
        push dx
        mov dx, 1000h
        mov ax, 0
    s1: sub ax, 1
        sbb dx, 0
        cmp ax, 0
        jne s1
        cmp dx, 0
        jne s1
        pop dx
        pop ax
        ret

; -------------------- 新的9号中断例程 -----------------------

int9:   push ax
        push bx
        push es

        in al, 60h

        pushf
        pushf
        pop bx
        and bh, 11111100b
        push bx
        call dword ptr ds:[0]   ; 对int指令进行模拟，调用原来的int 9中断例程
        
code ends
end start