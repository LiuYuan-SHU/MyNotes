assume cs:codeseg

codeseg segment
	dw 0123H,0456H,0789H,0abcH,0defH,0fedH,0cbaH,0987H
start:	mov	ax,0
		mov ds,ax
		mov bx,0

		mov cx,8
	s:	mov ax,[bx]
		mov cs:[bx],ax
		add bx,2
		loop s

		mov ax,4C00H
		int 21H
codeseg ends

end start