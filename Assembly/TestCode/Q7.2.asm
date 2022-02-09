;用si和di实现将字符串'welcome to masm!'复制到它后面的数据区中
assume cs:code,ds:data

data segment
	db	'welcome to masm!'
	db	'................'
data ends

code segment
start:
		mov ax,data
		mov ds,ax
		mov si,0
		mov di,16

		mov bx,0
		mov cx,16
	s:	mov ax,[si]
		mov [di],ax		
		add si,2
		add di,2
		loop s
;更简单的方法
;	s:	mov ax,0[si]
;		mov 16[si],ax
;		add si,2
;		loop s
		mov ax,4C00H
		int 21H
code ends

end start