/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/IntTy.h>
#include <orange/generator.h>

IntTy::IntTy(int width, bool isSigned) {
	m_width = width; 
	m_signed = isSigned; 
	m_llvm_ty = IntegerType::get(GE::runner()->context(), m_width);
}

std::string IntTy::getKeyStr(int width, bool isSigned) {
	std::stringstream ss; 
	if (isSigned == false) ss << "u";
	ss << "int" << width;
	return ss.str();	
}

std::string IntTy::string() const {
	return getKeyStr(m_width, m_signed);
}

std::string IntTy::typeSuffix() const {
	std::stringstream ss; 

	if (m_signed) ss << "i"; 
	else ss << "u"; 
	ss << m_width; 

	return ss.str();
}

IntTy* IntTy::getSigned(int width) {
	std::string keyStr = getKeyStr(width, true);
	if (getDefined(keyStr)) return (IntTy*)getDefined(keyStr);
	return (IntTy*)define(keyStr, new IntTy(width, true));
}

IntTy* IntTy::getUnsigned(int width) {
	std::string keyStr = getKeyStr(width, false);
	if (getDefined(keyStr)) return (IntTy*) getDefined(keyStr);
	return (IntTy*)define(keyStr, new IntTy(width, false));
}

IntTy* IntTy::get(int width, bool isSigned) {
	std::string keyStr = getKeyStr(width, isSigned);
	if (getDefined(keyStr)) return (IntTy*) getDefined(keyStr);
	return (IntTy*)define(keyStr, new IntTy(width, isSigned));
}


