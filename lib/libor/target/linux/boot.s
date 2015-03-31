[bits 64]
[section .text]
[global start]
[extern _@main]
start:
	call _@main
	
	mov rax, 60 ; syscalls on m
	mov rdi, 0
	syscall
	jmp $