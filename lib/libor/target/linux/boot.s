[bits 64]
[section .text]
[global _start]
[extern @main]
_start:
	call @main
	mov rdi, rax

	mov rax, 60 ; syscalls on m
	syscall
	jmp $
