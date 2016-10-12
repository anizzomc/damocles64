
; interrupt.asm
;
; Created on: Aug 28, 2011
;      Author: anizzomc
%include "arch/macros.m"

GLOBAL keyboardHandler
GLOBAL timerTickHandler
GLOBAL setPic1Mask

EXTERN foo
EXTERN keyIn

SECTION .text

keyboardHandler:
	pushaq
	mov rax, 0

	in	al, 60h ;Get keypressed
				;Argument already is int RAX

	mov rdi, 0
	mov rdi, rax
	call	keyIn

	mov	al, 20h ;Clear pick
	out	20h, al


	popaq
	iretq

timerTickHandler:
	pushaq
	call foo

	mov	al, 20h ;clear pic
	out	20h, al

	popaq
	iretq

setPic1Mask:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	out 21h, al

	mov rsp, rbp
	pop rbp
	ret
