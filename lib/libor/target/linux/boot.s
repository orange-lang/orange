.globl _start 

.text 
_start:
	pushq %rbp 
	callq __INTERNAL_main
	popq %rbp 
	movq %rax, %rdi 

	movq $60, %rax 
	syscall 
.exit:
	jmp .exit 
