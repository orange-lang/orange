[bits 64]
[section .text]
[global _start]
[extern __INTERNAL_main]
[extern ExitProcess]
_start:
	push rbp
	call __INTERNAL_main
	pop rbp
	
	mov rcx, rax
	call ExitProcess
	jmp $
