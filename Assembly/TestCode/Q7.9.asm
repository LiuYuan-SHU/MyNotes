;编程，将data段中每个单词的前四个字母改为大写字母
assume cs:code,ss:stack,ds:data

stack segment
	dw 0,0,0,0,0,0,0,0
stack ends
	
;第一个字母位于第四个字节，所以idata = 3
;两层循环
	;外层循环循环行，存储于bx中，每次bx+1，循环变量为4
	;内层循环循环列，存储于di中，每次di+1，循环变量为4
;所以寻址公式为：[bx+di+3]
data segment
	db '1. display      '
	db '2. brows        '
	db '3. replace      '
	db '4. modify       '
data ends

code segment
start:
;init
		mov ax,data
		mov ds,ax
		mov ax,stack
		mov ss,ax
		mov sp,16

		mov bx,0
		mov cx,4
	i:
		push cx

		mov cx,4
		mov di,0
		j:	mov al,[bx+di+3]
			and al,11011111B
			mov [bx+di+3],al
			inc di
			loop j

		pop cx
		add bx,16
		loop i

		mov ax,4C00H
		int 21H
code ends

end start