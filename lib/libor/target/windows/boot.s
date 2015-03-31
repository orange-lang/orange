.globl start 

.text 
start:
	pushq %rbp 
	callq __INTERNAL_main
	popq %rbp 

	mov %rax, %rcx 
	callq ExitProcess
.exit:
	jmp .exit 