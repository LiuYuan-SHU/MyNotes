assume	cs:codeseg

codeseg segment
	mov ax,0H
	mov cx,123
s:	add ax,ax+236
	loop s

	mov ax,4C00H
	int 21H
codeseg ends

end
