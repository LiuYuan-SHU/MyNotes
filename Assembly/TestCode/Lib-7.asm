;	编程,将data段中的年份 / 总收入 / 雇员人数按照顺序,
;	覆盖table段中的year / summ / ne,并计算人均收入,取整后覆盖??

assume cs:code,ds:data,ss:stack

data segment
	;表示21年的21个字符串
	db '1975','1976','1977','1978','1979','1980','1981','1982','1983'
	db '1984','1985','1986','1987','1988','1989','1990','1991','1992'
	db '1993','1994','1995'

	;表示21年公司总收入的21个dword型数据
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
	dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000

	;表示21年公司雇员人数的21个word型数据
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
	dw 11542,14430,15257,17800
data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

; 分析:
;	思路一:	采用分批完成的思想:将三组数据看作三个数组,一个一个数组向table中输入数据,即遍历table3次
		;难点与解决:	1.访问table中对应的数据:[bx].idata[si],一次顶多能够处理一个字的大小,因此对于double word类型的数据需要多处理一次
				;	2.每组数据完成之后不需要额外偏移,改变偏移量即可,那是否可以使用jmp指令?
;	思路二:	采用一次完整的思想:分别记录三组数据的开始地址,然后每完成一次就将这些地址增加相应的量
		;难点与解决:	1.
stack segment
	db 1000 dup (0)
stack ends

code segment
start1:	
		;init
		mov ax,data 	;数据区
		mov ds,ax
		mov ax,stack 	;栈区,用于存放循环变量和临时存放DS
		mov ss,ax
		mov sp,1000
		mov bx,table 	;将table的地址存放在di中,方便拿取
		mov di,bx
		mov bp,0 		;BP用于遍历整个DATA段

;先将年的信息写入结构化数据中
		mov cx,21
		mov bx,0		;bx用于遍历每一年,也就是一个结构体
year:
		push cx
		mov cx,4		;年份由4个byte组成,所以遍历四次(其实也可以用2个word解决)
		mov si,0		;[bx].idata[si],idata定位数组,si定位数组中的元素
	year_byte:
			mov al,ds:[bp]		;先将要复制的内容放在寄存器中
			push ds				;将DS暂存
			mov ds,di			;更改DS,使其指向table段
			mov [bx].0[si],al	;将要复制的内容放到目标位置
			pop ds
			inc si				;指向下一个byte
			inc bp
			loop year_byte
		pop cx
		add bx,10H				;处理完一年,指向下一年
		loop year

;复制收入
		mov bx,0				;重置BX,使目标回到第一年
		mov cx,21
summery:
		push cx
		mov cx,2
		mov si,0
	summery_doubleWord:
			mov ax,ds:[bp]
			push ds
			mov ds,di
			mov [bx].5[si],ax
			pop ds
			add si,2			;为了读取下一个word,偏移两个byte
			add bp,2
			loop summery_doubleWord
		pop cx
		add bx,10H
		loop summery

;复制雇员数量
		mov bx,0
		mov cx,21
staff:
		mov ax,ds:[bp]
		push ds
		mov ds,di
		mov [bx].10,ax
		pop ds
		add bx,10H
		add bp,2
		loop staff

;计算人均收入.由于收入是32位数据,因此采用高位存放在DX,低位存放在AX的计算方法
		mov bx,0
		mov cx,21
		mov ds,di				;由于不涉及拷贝,直接将DS设置为table段的首地址
ave:
		mov si,0
		mov ax,[bx].5[si]		;移入低位
		add si,2				;1word的偏移量
		mov dx,[bx].5[si]		;移入高位
		div word ptr [bx].10	;进行运算
		mov [bx].0DH,ax			;仅保留整数,于是将AX中的商放入目标位置
		add bx,10H
		loop ave

		mov ax,4C00H
		int 21H
code ends

end start1