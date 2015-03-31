.globl start 

.text 
start:
	pushq %rbp 
	callq $main 
	popq %rbp 
	movq %rax, %rdi 

	movq $60, %rax 
	syscall 
.exit:
	jmp .exit 
