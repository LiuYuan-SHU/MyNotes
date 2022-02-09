;编程，将data段中每一个单词的头一个字母改为大写字母
assume cs:code,ds:data

;可以发现，每一个单词的首字母位于当前16个字节中的第四个
;于是，idata = 4
;可以用bx存储data段的首地址，即0，所以没有必要存储
;用di来进行下一个单词的遍历
;于是寻址方式为：[di+4]，每次di向后移动16字节
;循环6次
data segment
	db '1. file         '
	db '2. edit         '
	db '3. search       '
	db '4. view         '
	db '5. options      '
	db '6. help         '
data ends

code segment
start:
;初始化DS
		mov ax,data
		mov ds,ax
;设置偏移地址DI
;设置循环次数CX
		mov di,0H
		mov cx,6H
	s:	mov bl,[di+3]		;按字节将需要改变的字符传入
		and bl,11011111B	;将字符进行与运算，令第6位变为0（ASCII - 32）
		mov [di+3],bl		;将结果传出
		add di,16			;指向下一个需要操作的字符
		loop s

		mov ax,4C00H
		int 21H
code ends

end start