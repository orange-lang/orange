/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

.globl WinMain

.text
WinMain:
	xor %rax, %rax
	pushq %rbp
	callq _main
	popq %rbp

	mov %rax, %rcx
	callq exit
.exit:
	jmp .exit
