/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_VALUES_H__
#define __ORANGE_VALUES_H__
#include "AST.h"
#include "AnyType.h"

class BaseVal : public Expression { 

};

class StrElement : public CodeElement {
private:
	std::string m_str; 
public:
	bool operator==(std::string RHS) {
		return m_str == RHS; 
	} 

	bool operator==(StrElement& RHS) {
		return m_str == RHS.m_str;
	}


	friend StrElement operator+(const char *s, StrElement& element);
	friend std::ostream& operator<< (std::ostream& stream, const StrElement& element);

	operator std::string() const { return m_str; }

	StrElement(std::string str) : m_str(str) {}
	StrElement(const char *str) : m_str(str) {}
};

class ValFactory {
public:
	std::string value;
	std::string size;

	BaseVal *produce();
};


class UIntVal : public BaseVal {
public:
	virtual std::string getClass() { return "UIntVal"; }

	Value* Codegen();

	uint64_t value;
	uint8_t size;

	virtual bool isSigned() { return false; }

	virtual std::string string() {
		std::stringstream ss;
		ss << "(uint" << (uint64_t)size << ")" << value;
		return ss.str();
	}

	virtual AnyType *getType() { 
		return AnyType::getUIntNTy(size); 
	}

	virtual ASTNode* clone() { 
		UIntVal *ret = new UIntVal(value, size); 
		return ret;
	}


	UIntVal() { }
	UIntVal(uint64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value.
};

class IntVal : public BaseVal {
public:
	virtual std::string getClass() { return "IntVal"; }

	Value* Codegen();

	int64_t value;
	uint8_t size;

	virtual bool isSigned() { return true; }

	virtual std::string string() {
		std::stringstream ss;
		ss << "(int" << (uint64_t)size << ")" << value;
		return ss.str();
	}

	virtual AnyType *getType() { 
		return AnyType::getIntNTy(size); 
	}

	virtual ASTNode* clone() { 
		IntVal* ret = new IntVal(value, size);
		return ret;
	}

	IntVal() { }
	IntVal(int64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value.
};

class FloatVal : public BaseVal {
public:
	virtual std::string getClass() { return "FloatVal"; }

	Value* Codegen();

	float value;

	virtual std::string string() {
		std::stringstream ss;
		ss << "(float)" << value;
		return ss.str();
	}

	virtual AnyType *getType() { 
		return AnyType::getFloatTy(); 
	}

	virtual ASTNode* clone() { 
		FloatVal* ret = new FloatVal(value);
		return ret;
	}

	FloatVal();
	FloatVal(float val) : value(val) {} // parses a string into its value.
};

class DoubleVal : public BaseVal {
public:
	virtual std::string getClass() { return "DoubleVal"; }

	Value* Codegen();

	double value;

	virtual std::string string() {
		std::stringstream ss;
		ss << "(double)" << value;
		return ss.str();
	}

	virtual AnyType *getType() { 
		return AnyType::getDoubleTy(); 
	}

	virtual ASTNode* clone() { 
		DoubleVal* ret = new DoubleVal(value);
		return ret;
	}

	DoubleVal();
	DoubleVal(double val) : value(val) {} // parses a string into its value.
};

#endif 