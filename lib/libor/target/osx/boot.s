.globl start 

.text 
start:
	andq $0xfffffffffffffff0, %rsp 
	callq _$main
	movq %rax, %rdi 

	# syscall number: rax + 0x2000000 (+ 0x2000000 is a mac thing) 
	# arguments: rdi, rsi, rdx, r10, r8, r9
	movl $0x2000001, %eax 
	syscall
.exit:
	jmp .exit 
