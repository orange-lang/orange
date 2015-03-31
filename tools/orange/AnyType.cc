/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/AnyType.h>

AnyType::AnyType(Type* type, bool isSigned) {
	m_type = type; 
	m_signed = isSigned; 

	m_type_str = "";

	if (type->isIntegerTy()) {
		if (isSigned == false) m_type_str += "u";
		m_type_str += "int";
		m_type_str += type->getIntegerBitWidth();
	} else if (type->isFloatTy()) {
		m_type_str = "float"; 
	} else if (type->isDoubleTy()) {
		m_type_str = "double";
	} else if (type->isVoidTy()) {
		m_type_str = "void";
	}

}

AnyType::AnyType(std::string type) {
	m_type_str = type; 
	m_signed = false; 

	if (type == "char" || type == "int8") {
		m_type = Type::getIntNTy(getGlobalContext(), 8);
		m_signed = true;
	} else if (type == "uchar" || type == "uint8") {
		m_type = Type::getIntNTy(getGlobalContext(), 8);
	} else if (type == "int16") {
		m_type = Type::getIntNTy(getGlobalContext(), 16);
		m_signed = true;
	} else if (type == "uint16") {
		m_type = Type::getIntNTy(getGlobalContext(), 16);
	} else if (type == "int32") {
		m_type = Type::getIntNTy(getGlobalContext(), 32);
		m_signed = true;
	} else if (type == "uint32") {
		m_type = Type::getIntNTy(getGlobalContext(), 32);
	} else if (type == "int" || type == "int64") {
		m_type = Type::getIntNTy(getGlobalContext(), 64);
		m_signed = true;
	} else if (type == "uint" || type == "uint64") {
		m_type = Type::getIntNTy(getGlobalContext(), 64);
	} else if (type == "float") {
		m_type = Type::getFloatTy(getGlobalContext());
	} else if (type == "double") {
		m_type = Type::getDoubleTy(getGlobalContext());
	} else if (type == "void") {
		m_type = Type::getVoidTy(getGlobalContext());
	} else {
		throw std::runtime_error("Invalid type " + type);
	}
}