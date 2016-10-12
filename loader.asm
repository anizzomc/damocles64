global loader
global eokl
extern main

section .text
align 8
STACKSIZE equ 0x4000

loader:
	mov rsp, stack+STACKSIZE
	call main
cicle:
	hlt
	jmp cicle


eokl	dd STACKSIZE + stack
section .bss
	align 32
	stack:
	resb STACKSIZE
