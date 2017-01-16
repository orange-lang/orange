/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

.globl start

.text
start:
	xor %rax, %rax
	andq $0xfffffffffffffff0, %rsp
	callq __main
	movq %rax, %rdi

	# syscall number: rax + 0x2000000 (+ 0x2000000 is a mac thing)
	# arguments: rdi, rsi, rdx, r10, r8, r9
	movl $0x2000001, %eax
	syscall
.exit:
	jmp .exit
