[bits 64]
[section .text]
[global _start]
[extern @main]
_start:
	call @main
	
	mov rax, 60 ; syscalls on m
	mov rdi, 0
	syscall
	jmp $
