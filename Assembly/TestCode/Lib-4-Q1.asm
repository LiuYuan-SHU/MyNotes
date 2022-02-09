assume cs:code
;要求：向内存0:200~0:23F传送数据0~63(3FH)
code segment
	mov ax,0
	mov es,ax
	mov bx,0
	mov cx,64
s:	mov es:[bl],bl
	inc bl
	loop s

	mov ax,4C00H
	int 21H
code ends

end