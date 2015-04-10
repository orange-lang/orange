/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <iostream>
#include <sstream>

#include <orange/AnyType.h>
#include <orange/generator.h>

std::map<std::string, AnyType*> AnyType::m_defined_tyes;

AnyType::AnyType(Type* type, bool isSigned) {
	m_type = type; 
	m_signed = isSigned; 

	m_type_str = "";

	int num_ptrs = 0; 
	while (type->isPointerTy()) {
		type = type->getPointerElementType();

		num_ptrs++;
	}

	m_ptrs = num_ptrs;

	if (type->isIntegerTy()) {
		std::stringstream ss; 
		if (isSigned == false) ss << "u";
		ss << "int" << type->getIntegerBitWidth(); 
		m_type_str = ss.str();
	} else if (type->isFloatTy()) {
		m_type_str = "float"; 
	} else if (type->isDoubleTy()) {
		m_type_str = "double";
	} else if (type->isVoidTy()) {
		m_type_str = "void";
	} else {
		throw std::runtime_error("Cannot create AnyType!\n");
	}
}

std::string AnyType::string() const {
	std::stringstream ss;
	ss << m_type_str; 
	for (int i = 0; i < m_ptrs; i++) ss << "*";
	return ss.str();
}

bool AnyType::isIDTy() const {
	return m_type_str == "id";
}

bool AnyType::isVoidTy() const {
	return m_type_str == "void";
}

bool AnyType::isIntegerTy() const {
	return m_type->isIntegerTy();
}

bool AnyType::isFloatTy() const {
	return m_type_str == "float";
}

bool AnyType::isDoubleTy() const {
	return m_type_str == "double";
}

bool AnyType::isFloatingPointTy() const {
	return isFloatTy() || isDoubleTy();
}

int AnyType::getIntegerBitWidth() const {
	return m_type->getIntegerBitWidth();
}


AnyType::AnyType(std::string type, int ptrs) {
	m_type_str = type; 
	m_signed = false; 

	if (type == "char" || type == "int8") {
		m_type = Type::getIntNTy(GE::runner()->context(), 8);
		m_signed = true;
	} else if (type == "uchar" || type == "uint8") {
		m_type = Type::getIntNTy(GE::runner()->context(), 8);
	} else if (type == "uint1") {
		m_type = Type::getIntNTy(GE::runner()->context(), 1);
	} else if (type == "int16") {
		m_type = Type::getIntNTy(GE::runner()->context(), 16);
		m_signed = true;
	} else if (type == "uint16") {
		m_type = Type::getIntNTy(GE::runner()->context(), 16);
	} else if (type == "int32") {
		m_type = Type::getIntNTy(GE::runner()->context(), 32);
		m_signed = true;
	} else if (type == "uint32") {
		m_type = Type::getIntNTy(GE::runner()->context(), 32);
	} else if (type == "int" || type == "int64") {
		m_type = Type::getIntNTy(GE::runner()->context(), 64);
		m_signed = true;
	} else if (type == "uint" || type == "uint64") {
		m_type = Type::getIntNTy(GE::runner()->context(), 64);
	} else if (type == "float") {
		m_type = Type::getFloatTy(GE::runner()->context());
	} else if (type == "double") {
		m_type = Type::getDoubleTy(GE::runner()->context());
	} else if (type == "void") {
		m_type = Type::getVoidTy(GE::runner()->context());
	} else if (type == "id") {
		m_type = Type::getVoidTy(GE::runner()->context());
	} else {
		throw std::runtime_error("Invalid type " + type);
	}

	m_ptrs = ptrs; 

	for (int i = 0; i < m_ptrs; i++) {
		m_type = m_type->getPointerTo();
	}
}

AnyType* AnyType::getIDTy() {
	if (m_defined_tyes.find("id") != m_defined_tyes.end()) {
		return m_defined_tyes.find("id")->second;
	}

	AnyType* voidTy = new AnyType("id");
	m_defined_tyes["id"] = voidTy; 
	return voidTy;
}


AnyType* AnyType::getVoidTy() {
	if (m_defined_tyes.find("void") != m_defined_tyes.end()) {
		return m_defined_tyes.find("void")->second;
	}

	AnyType* voidTy = new AnyType("void");
	m_defined_tyes["void"] = voidTy; 
	return voidTy;
}

AnyType* AnyType::getUIntNTy(int size) {
	std::stringstream ss;
	ss << "uint" << size;

	if (m_defined_tyes.find(ss.str()) != m_defined_tyes.end()) {
		return m_defined_tyes.find(ss.str())->second;
	}

	AnyType* voidTy = new AnyType(ss.str());
	m_defined_tyes[ss.str()] = voidTy; 
	return voidTy;
}

AnyType* AnyType::getIntNTy(int size) {
	std::stringstream ss;
	ss << "int" << size;

	if (m_defined_tyes.find(ss.str()) != m_defined_tyes.end()) {
		return m_defined_tyes.find(ss.str())->second;
	}

	AnyType* voidTy = new AnyType(ss.str());
	m_defined_tyes[ss.str()] = voidTy; 
	return voidTy;
}

AnyType* AnyType::getFloatTy() {
	if (m_defined_tyes.find("float") != m_defined_tyes.end()) {
		return m_defined_tyes.find("float")->second;
	}

	AnyType* voidTy = new AnyType("float");
	m_defined_tyes["float"] = voidTy; 
	return voidTy;
}

AnyType* AnyType::getDoubleTy() {
	if (m_defined_tyes.find("double") != m_defined_tyes.end()) {
		return m_defined_tyes.find("double")->second;
	}

	AnyType* voidTy = new AnyType("double");
	m_defined_tyes["double"] = voidTy; 
	return voidTy;
}

AnyType* AnyType::getInt8PtrTy() {
	if (m_defined_tyes.find("int8*") != m_defined_tyes.end()) {
		return m_defined_tyes.find("int8*")->second;
	}

	AnyType* voidTy = new AnyType("int8", 1);
	m_defined_tyes["int8*"] = voidTy; 
	return voidTy;
}
