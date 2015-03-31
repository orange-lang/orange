.globl WinMain 

.text 
WinMain:
	xor %rax, %rax
	pushq %rbp 
	callq __INTERNAL_main
	popq %rbp 

	mov %rax, %rcx 
	callq exit
.exit:
	jmp .exit 
