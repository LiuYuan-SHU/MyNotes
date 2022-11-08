assume cs:code

code segment
start:  mov al, 2
        out 70h, al
        mov al, 0
        out 71h, al   
code ends
end start