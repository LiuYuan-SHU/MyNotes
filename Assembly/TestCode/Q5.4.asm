assume cs:code

code segment
	mov ax,0ffffH
	mov ds,ax			;initialize DS, add DS:[BX] to DX
	mov dx,0			;initialize register DX to restore the result
	mov ax,0			;use AX to temporarily store the num
	mov bx,0			;loop DS:[0] to DS:[9]
	mov cx,9			;control the range of loop
s:	mov al,[bx]			;mov al,DS:[bx]
	add dx,ax			;8 Byte -> 16 Byte
	inc bx				;bx += 1
	loop s
	
	mov ax,4C00H
	int 21H
code ends

end