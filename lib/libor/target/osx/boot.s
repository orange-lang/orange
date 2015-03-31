[bits 64]
[section .text]
[global start]
[extern _@main]
start:
	and esp, 0xfff8
	push rbp
	call _@main
	pop rbp
	mov rdi, rax
	
	; syscall number: rax + 0x2000000 (+ 0x2000000 is a mac thing) 
	; arguments: rdi, rsi, rdx, r10, r8, r9
	mov rax, 0x2000001
	syscall
	jmp $