/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

.globl _start

.text
_start:
	xor %rax, %rax
	andq $0xfffffffffffffff0, %rsp
	callq _main
	movq %rax, %rdi

	movq $60, %rax
	syscall
.exit:
	jmp .exit
