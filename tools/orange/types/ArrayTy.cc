/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <sstream>
#include <orange/types/ArrayTy.h>

ArrayTy::ArrayTy(OrangeTy* internalTy, unsigned int count) {
	m_internal_ty = internalTy; 
	m_count = count; 
	m_llvm_ty = ArrayType::get(internalTy->getLLVMType(), count);
}

std::string ArrayTy::string() const {
	std::stringstream ss; 
	ss << m_internal_ty->string() << "[" << m_count << "]";
	return ss.str();
}

bool ArrayTy::isSigned() const {
	return m_internal_ty->isSigned();
}

ArrayTy* ArrayTy::get(OrangeTy* internalTy, unsigned int count) {
	std::stringstream ss; 
	ss << internalTy->string() << "[" << count << "]";
	std::string keyStr = ss.str();
	if (getDefined(keyStr)) return (ArrayTy*)getDefined(keyStr);
	return (ArrayTy*)define(keyStr, new ArrayTy(internalTy, count));
}
