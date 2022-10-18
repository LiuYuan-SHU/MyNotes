assume cs:codeseg

codeseg segment
        mov ax, 4C00H       ; 可以看到结束代码在这
        int 21H

start:  mov ax, 0           ; 程序从这开始运行，现在 ax 中是 0
    s:  nop                 ; 什么都不做，占用一个指令周期
        nop

        mov di, offset s    ; di 现在是 s 的偏移地址
        mov si, offset s2   ; si 现在是 s2 的偏移地址
        mov ax, cs:[si]     ; 将 s2 开始的2个字节放到 ax 中
        mov cs:[di], ax     ; 将 ax 中的内容放到 s 的开头，覆盖 nop

    s0: jmp short s         ; jmp 到 s 重新运行 --> jmp short s1

    s1: mov ax, 0           ; int 21H, ah = 0 --> 程序终止
        int 21H
        mov ax, 0

    s2: jmp short s1
        nop
    
codeseg ends
end start
