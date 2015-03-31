.globl _start 

.text 
_start:
	xor %rax, %rax
	andq $0xfffffffffffffff0, %rsp
	callq __INTERNAL_main
	movq %rax, %rdi 

	movq $60, %rax 
	syscall 
.exit:
	jmp .exit 
