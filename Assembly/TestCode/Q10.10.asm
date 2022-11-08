; 编程，计算data段中第一组数据的3次方，结果保存在后面一组dword单元中

assume cs:code

data segment
    dw  1, 2, 3, 4, 5, 6, 7, 8
    dd  0, 0, 0, 0, 0, 0, 0, 0
data ends

code segment
start:  
        ; init
        mov ax, data
        mov ds, ax

        mov cx, 9
        mov bx, 0
        mov di, 0
    calculate:
        ; n * n
        mov al, byte ptr ds:[bx]
        mul byte ptr ds:[bx]
        ; n^2 stores in ax
        ; we just multiple it again
        mul word ptr ds:[bx]
        ; restore the result into data segment
        mov word ptr ds:[bx + di + 16], ax
        mov word ptr ds:[bx + di + 18], dx

        ; increase bx
        add bx, 2
        ; increase bi
        add di, 2
        ; loop
        loop calculate

        mov ax, 4C00H
        int 21H
    code ends
end start