assume cs:code
code segment
	mov ax,0
	mov ds,ax
	mov bx,0200H
	mov dx,0h

	mov cx,64
s:	mov ds:[bx],dl
	inc bx
	inc dx
	loop s

	mov ax,4C00H
	int 21H
code ends
end