; smallhello.s
; Kenneth B. Jensen, 2017-03-15
; This program is part of the public domian

; compilation:
;     $ nasm -f bin -o a.out smallhello.s
; add '-l smallhello.lst' to view machine code
; note a.out isn't marked executable, "chmod +x" it

; assembled is 125 bytes, machine code is below:
; 7F45 4C46 0201 FFC3 B970 0001 00EB 1900 0200 3E00 0100 0000 0600 0100 0000 0000
; 3800 0000 0000 0000 B004 B20D CD80 30C0 FEC0 CD80 5000 3800 0100 0000 0500 0000
; 0000 0000 0000 0000 0000 0100 0000 0000 6300 0000 0000 0000 7D00 0000 0000 0000
; 7D00 0000 0000 0000 0000 0000 0000 0000 4865 6C6C 6F2C 2057 6F72 6C64 0A

BITS 64
CPU X64

	org	0x00010000

Elf64_Ehdr:
		db 0x7F, "ELF"          ; e_ident[EI_MAG0 -> EI_MAG3]
		db 0x02                 ; e_ident[EI_CLASS] (64-bit)
		db 0x01                 ; e_ident[EI_DATA] (litte-endian)
_start:
		inc ebx
		mov ecx, msg
		jmp _mid
		db 0x00

		dw 0x0002                 ; e_type (executable)
		dw 0x003E                 ; e_machine (x86_64)
		dd 0x00000001             ; e_version

		dq _start               ; e_entry
		dq Elf64_Phdr - $$      ; e_phoff
_mid:
		mov al, 4
		mov dl, len
		int 0x80 ; e_shoff
		xor al, al
		inc al
		int 0x80
		dw Elf64_Ehdrsz         ; e_ehsize
		dw Elf64_Phdrsz         ; e_phentsize
Elf64_Phdr:
		dd 0x01                 ; e_phnum, p_type
		dd 0x05                 ; e_shentsize, p_flags ;; modifyable
		dq 0x00                 ; e_shnum, p_offset
		dq $$                   ; e_shstrndx, p_vaddr


Elf64_Ehdrsz	equ $ - Elf64_Ehdr

		dq 99           ; p_paddr
		dq filesz       ; p_filesz
		dq filesz       ; p_memsz
		dq 0x0000       ; p_align

Elf64_Phdrsz	equ $ - Elf64_Phdr

msg 		equ $
		db "Hello, World", 0xA
len		equ $ - msg

filesz		equ $ - $$
