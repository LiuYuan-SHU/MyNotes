assume cs:code,ds:data

data segment
	db 'Basic'
	db 'iNfOrMaTiOn'
data ends

code segment
start:	
		mov ax,data
		mov ds,ax

;将Basic全部转换为大写字母
		mov bx,0
		mov cx,5			;Basic占位5位
	s1:	mov al,[bx]			;将值复制出来，操作完后放回
		and al,11011111B	;将第六位变为0，其他位不变
		mov [bx],al
		inc bx
		loop s1

;将iNfOrMaTiOn全部变为小写字母
		mov bx,5			;设置(bx) = 5，指向"iN..."的第一个字母
		mov cx,11
	s0:	mov al,[bx]
		or al,00100000B		;将第六位变为1，其他位不变
		mov [bx],al
		inc bx
		loop s0

		mov ax,4C00H
		int 21H
code ends

end start