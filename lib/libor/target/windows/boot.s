.globl start 

.text 
start:
	xor %rax, %rax
	pushq %rbp 
	callq __INTERNAL_main
	popq %rbp 

	mov %rax, %rcx 
	callq ExitProcess
.exit:
	jmp .exit 