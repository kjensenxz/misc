; true.s - return 0 without GNU bloat 
; This program is public domain - Kenneth B. Jensen <kenneth@jensen.cf>
global _start
_start:
	mov eax, 1
	xor ebx, ebx
	int 0x80
