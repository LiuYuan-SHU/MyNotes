;	编程,利用除法指令计算 100001/100
;	分析:100001 = 186A1H > 65535,即超出16位二进制的范围,因此,
;	采用32位存放被除数,用16位存放除数,即将100001存放于DX和AX中

assume cs:code

code segment
	mov dx,1
	mov ax,86A1H
	mov bx,100
	div bx

	mov ax,4C00H
	int 21H
code ends

end