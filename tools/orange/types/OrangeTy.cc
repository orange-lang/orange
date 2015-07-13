/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/OrangeTy.h>
#include <orange/types/PointerTy.h>
#include <orange/generator.h>
#include <orange/Values.h>
#include <sstream>

std::map<std::string, OrangeTy*> OrangeTy::m_defined_types;

OrangeTy* OrangeTy::getDefined(std::string name) {
	if (m_defined_types.find(name) != m_defined_types.end()) {
		return m_defined_types.find(name)->second; 
	}

	return nullptr;
}

OrangeTy* OrangeTy::define(std::string name, OrangeTy* type) {
	m_defined_types[name] = type;
	return type;
}

OrangeTy* OrangeTy::getPointerTo() {
	return PointerTy::get(this);
}

Value* OrangeTy::allocate() {
	if (getLLVMType() == nullptr) {
		std::stringstream ss;
		ss << "getLLVMType() returned nullptr! Type is " << string() << std::endl;
		throw std::runtime_error(ss.str());
	}
	
	return GE::builder()->CreateAlloca(getLLVMType());
}

OrangeTy* OrangeTy::get(std::string str) {
	if      (str == "char") 		return IntTy::getSigned(8);
	else if (str == "int") 			return IntTy::getSigned(64);
	else if (str == "uint")			return IntTy::getUnsigned(64);
	else if (str == "int8")			return IntTy::getSigned(8);
	else if (str == "uint8")		return IntTy::getUnsigned(8);
	else if (str == "int16")		return IntTy::getSigned(16);
	else if (str == "uint16")		return IntTy::getUnsigned(16);
	else if (str == "int32")		return IntTy::getSigned(32);
	else if (str == "uint32")		return IntTy::getUnsigned(32);
	else if (str == "int64")		return IntTy::getSigned(64);
	else if (str == "uint64")		return IntTy::getUnsigned(64);
	else if (str == "float")		return FloatTy::get();
	else if (str == "double")		return DoubleTy::get();
	else if (str == "void")			return VoidTy::get();
	else if (str == "id")				return IDTy::get();
	else if (str == "var")			return VarTy::get();

	// default case 
	return VoidTy::get();
}

bool OrangeTy::isExpressionValidForConstArray(Expression* e) {
	return e->isConstant();
}

unsigned int OrangeTy::valueFromExpression(Expression* e) {
	if (e->getClass() != "UIntVal" && e->getClass() != "IntVal") {
		throw CompilerMessage(*e, "can only use integers for the size of an array!");
	}

	if (e->getClass() == "UIntVal") {
		UIntVal* uintval = (UIntVal*)e; 
		return (unsigned int)uintval->value;
	} else if (e->getClass() == "IntVal") {
		IntVal* intval = (IntVal*)e; 

		if (intval < 0) {
			throw CompilerMessage(*e, "the size of an array cannot be negative!");
		}

		return (unsigned int)intval->value; 
	}

	return 0;
}

