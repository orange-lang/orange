/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/VariadicArrayTy.h>
#include <orange/AST.h>

VariadicArrayTy::VariadicArrayTy(OrangeTy* internalTy, Expression* count) {	
	m_internal_ty = internalTy; 
	m_count = count;	
	m_llvm_ty = internalTy->getPointerTo()->getLLVMType();
}

std::string VariadicArrayTy::string() const {
	return m_internal_ty->string() + "[" + m_count->string() + "]";  
}

bool VariadicArrayTy::isSigned() const {
	return m_internal_ty->isSigned();
}

VariadicArrayTy* VariadicArrayTy::get(OrangeTy* internalTy, Expression* count) {
	std::stringstream ss; 
	ss << internalTy->string() << "[" << (unsigned long long)count << "]";
	std::string keyStr = ss.str();
	if (getDefined(keyStr)) return (VariadicArrayTy*)getDefined(keyStr);
	return (VariadicArrayTy*)define(keyStr, new VariadicArrayTy(internalTy, count));
}
