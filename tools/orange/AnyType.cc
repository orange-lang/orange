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
#include <orange/Values.h>

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

	while (type->isArrayTy()) {
		m_arrays.insert(m_arrays.begin(), type->getArrayNumElements());
		type = type->getArrayElementType();
	}

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
	for (int arraysz : m_arrays) {
		ss << "[" << arraysz << "]";
	}

	for (auto array_expr : m_arrays_expr) {
		array_expr->resolve();
		ss << "[" << array_expr->string() << "]";
	}

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

AnyType* AnyType::getPointerTo() {
	AnyType* retType = new AnyType(m_type_str, std::vector<int>(), m_ptrs + 1);
	return retType;
}

AnyType* AnyType::getPointerElementType() {
	if (m_ptrs == 0) {
		throw CompilerMessage(*this, "Not a pointer!");
	}

	std::stringstream ss; 
	ss << m_type_str; 

	for (int array : m_arrays) {
		ss << "[" << array << "]";
	} 

	ss << (m_ptrs - 1); 
	std::string type = ss.str();

	if (m_defined_tyes.find(type) != m_defined_tyes.end()) {
		return m_defined_tyes.find(type)->second; 
	}

	AnyType* someTy = new AnyType(m_type_str, m_arrays, m_ptrs - 1);
	m_defined_tyes[type] = someTy; 
	return someTy; 
}


AnyType::AnyType(std::string type, std::vector<int> arrays, int ptrs) {
	m_type_str = type; 
	m_signed = false; 
	m_arrays = arrays;

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

	for (int i = m_arrays.size() - 1; i >= 0; i--) {
		m_type = ArrayType::get(m_type, m_arrays[i]);
	}
}

AnyType::AnyType(std::string type, std::vector<Expression*> arrayExpr, int ptrs) {
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

	// Now we need to detect if it's a variable-sized array.
	bool variable_sized = false;

	for (auto expr : arrayExpr) {
		if (expr->isConstant() == false) {
			variable_sized = true; 
			break; 
		}
	}

	if (variable_sized == true) {
		for (int i = arrayExpr.size() - 1; i >= 0; i--) {
			m_arrays_expr.push_back(arrayExpr[i]);
			m_type = m_type->getPointerTo();
		}
	} else {
		// All of the expressions here are constant


		for (int i = 0; i < arrayExpr.size(); i++) {
			auto expr = arrayExpr[i];

			if (expr->getClass() != "UIntVal" && expr->getClass() != "IntVal") {
				throw CompilerMessage(*this, "can only use integers for the size of an array!");
			}

			if (expr->getClass() == "UIntVal") {
				UIntVal* uintval = (UIntVal*)expr; 
				m_arrays.push_back((int)uintval->value);			
			} else {
				IntVal* intval = (IntVal*)expr; 
				m_arrays.push_back((int)intval->value);							
			}
		}

		for (int i = m_arrays.size() - 1; i >= 0; i--) {
			m_type = ArrayType::get(m_type, m_arrays[i]);
		}
	}


}

AnyType* AnyType::getElementType() {
	if (m_arrays.size() == 0) {
		throw CompilerMessage(*this, "Not an array!");
	}

	std::vector<int> arrays = m_arrays; 
	arrays.pop_back();

	std::stringstream ss; 
	ss << m_type_str; 

	for (int array : arrays) {
		ss << "[" << array << "]";
	} 

	ss << m_ptrs; 
	std::string type = ss.str();

	if (m_defined_tyes.find(type) != m_defined_tyes.end()) {
		return m_defined_tyes.find(type)->second; 
	}

	AnyType* someTy = new AnyType(m_type_str, arrays, m_ptrs);
	m_defined_tyes[type] = someTy; 
	return someTy; 
}

AnyType* AnyType::getBaseType() {
	if (m_defined_tyes.find(m_type_str) != m_defined_tyes.end()) {
		return m_defined_tyes.find(m_type_str)->second; 
	}	

	AnyType* someTy = new AnyType(m_type_str, std::vector<int>(), 0);
	m_defined_tyes[m_type_str] = someTy; 
	return someTy;
}

AnyType* AnyType::getArray(int size) {
	std::stringstream ss; 
	ss << m_type_str; 

	// Add on existing arrays 
	for (auto array : m_arrays) {
		ss << "[" << array << "]";
	}

	ss << "[" << size << "]" << m_ptrs; 
	std::string type = ss.str();

	if (m_defined_tyes.find(type) != m_defined_tyes.end()) {
		return m_defined_tyes.find(type)->second;
	}

	std::vector<int> arrays = m_arrays; 
	arrays.push_back(size);

	AnyType* arrayTy = new AnyType(m_type_str, arrays, m_ptrs);
	m_defined_tyes[type] = arrayTy;
	return arrayTy;
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

	AnyType* voidTy = new AnyType("int8", std::vector<int>(), 1);
	m_defined_tyes["int8*"] = voidTy; 
	return voidTy;
}

Value* AnyType::allocate() {
	return GE::builder()->CreateAlloca(getLLVMType());
}

bool AnyType::isConstantArray() const { 
	if (m_arrays.size() > 0 && m_arrays_expr.size() == 0) return true; 
	return false;
}

