; false.s - return 1 without GNU bloat 
; This program is public domain - Kenneth B. Jensen <kenneth@jensen.cf>
global _start
_start:
	mov eax, 1
	mov ebx, 1
	int 0x80
