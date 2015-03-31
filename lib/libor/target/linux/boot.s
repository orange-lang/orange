[bits 64]
[section .text]
[global _start]
[extern @main]
_start:
	and esp, 0xfff8
	push rbp
	call _@main
	pop rbp
	mov rdi, rax
	
	mov rax, 60 ; syscalls on m
	syscall
	jmp $
