
bits 32
start:
mov eax, [esp+4]
add eax, string-start
mov ebx, eax
int 31
ret

string db "abc", 0xA , "best os eveeeer!!", 0
