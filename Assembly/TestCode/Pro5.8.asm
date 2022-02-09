assume cs:code
;将内存 ffff:0~ffff:b 单元中的数据复制到 0:200~0:20b 单元中
code segment
	;iniliazation
	mov ax,0ffffH
	mov ds,ax
	mov ax,0
	mov es,ax

	mov cx,0bH		;控制遍历范围
	mov bx,0		;将DS:[BX]复制给ES:[BX]

s:	mov al,ds:[bx]	;不能够 mov es:[bx],ds:[bx]
	mov es:[bx],al
	inc bx
	loop s

	mov ax,4C00H
	int 21H

code ends

end