assume cs:code

code segment
	mov ax,0ffffh
	mov ds,ax
	mov bx,6		;设置ds:bx指向ffff:6
				
	mov al,[bx]		
	mov ah,0	
						
	mov dx,0
									
	mov cx,3
s:	add dx,ax
	loop s
												
	mov ax,4C00H
	int 21H			;程序返回
code ends

end
