assume cs:code

code segment
	mov ax,0ffffH
	mov ds,ax
	mov bx,6

	mov al,[bx]
	mov ah,0

	mov dx,0
	mov cx,123
s:	add dx,ax
	loop s

	mov ax,4C00H
	int 21H
code ends

end
