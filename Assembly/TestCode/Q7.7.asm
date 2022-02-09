;编程，将data段中的每个单词改为大写字母
assume cs:code,ds:data,ss:stack

;要解决这个问题，需要两层循环
	;第一层循环用来遍历当前的列（16个字节）
	;第二层循环用来遍历四行
;于是用bx来遍历行，所以bx每次增加16
	;于是外层循环的循环次数为4
;于是用di来遍历列，所以di每次增加1
	;于是内层循环的循环次数为16
;于是寻址公式：[bx+di]
data segment
	db 'ibm             '
	db 'dec             '
	db 'dos             '
	db 'vax             '
data ends

;以栈的方式，用8个字的内存空间存放内外层循环交替时的数据
stack segment
	dw 0,0,0,0,0,0,0
stack ends

code segment
start:
;initialization
		mov ax,data
		mov ds,ax
		mov ax,stack
		mov ss,ax
		mov sp,16

;外层循环，初始化外层遍历变量bx和外层循环变量CX
		mov bx,0
		mov cx,4
	i:	
		push cx					;记录当前循环变量
		mov cx,16				;初始化内层循环变量
		mov di,0				;初始化内层遍历变量DI
		j:
			;以字节方式传入，处理后传出
			mov al,[bx+di]
			and al,11011111B
			mov [bx+di],al
			inc di
			loop j
		
		add bx,16				;向后移动16字节，处理下一行
		pop cx					;恢复外层循环变量
		loop i

		mov ax,4C00H
		int 21H
code ends

end start