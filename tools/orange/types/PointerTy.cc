/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/PointerTy.h>
#include <orange/error.h>

PointerTy::PointerTy(OrangeTy* pointerElement) {
	m_pointer = pointerElement; 
	m_llvm_ty = pointerElement->getLLVMType()->getPointerTo();
}

std::string PointerTy::string() const {
	return m_pointer->string() + "*";
}

bool PointerTy::isSigned() const {
	return m_pointer->isSigned();
}

PointerTy* PointerTy::get(OrangeTy* pointerElement) {
	if (pointerElement->isVoidTy()) {
		throw CompilerMessage(*pointerElement, "Cannot get a pointer to void type!");
	}

	if (pointerElement->isIDTy()) {
		throw CompilerMessage(*pointerElement, "Cannot get a pointer to a type that hasn't been determined!");
	}

	std::string keyStr = pointerElement->string() + "*"; 
	if (getDefined(keyStr)) return (PointerTy*)getDefined(keyStr);
	return (PointerTy*)define(keyStr, new PointerTy(pointerElement));
}
