assume cs:codeseg

codeseg segment
	dw 0123H,0456H,0789H,0abcH,0defH,0fedH,0cbaH,0987H
	dw 0,0,0,0,0,0,0,0,0,0
start:	mov ax,cs
		mov ss,ax
		mov sp,23H	;第一个dw8个数据，占用f，接下来有10个字，f + 10 * 2 = 23H
		
		mov ax,0
		mov ds,ax
		mov bx,0
		mov cx,8
	s:	push [bx]
		pop cs:[bx]
		add bx,2
		loop s

		mov ax,4c00h
		int 21h
codeseg ends

end start