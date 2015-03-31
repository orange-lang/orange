#ifndef __VALUES_H__
#define __VALUES_H__
#include "AST.h"

class UIntVal : public BaseVal {
public:
	Value* Codegen();

	uint64_t value;
	uint8_t size;

	virtual std::string string() {
		std::stringstream ss;
		ss << "(uint" << (uint64_t)size << ")" << value;
		return ss.str();
	}

	virtual Type *getType() { 
		return Type::getIntNTy(getGlobalContext(), size); 
	}


	UIntVal() { }
	UIntVal(uint64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value.
};

class IntVal : public BaseVal {
public:
	Value* Codegen();

	int64_t value;
	uint8_t size;

	virtual std::string string() {
		std::stringstream ss;
		ss << "(int" << (uint64_t)size << ")" << value;
		return ss.str();
	}

	virtual Type *getType() { 
		return Type::getIntNTy(getGlobalContext(), size); 
	}


	IntVal() { }
	IntVal(int64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value.
};

class FloatVal : public BaseVal {
public:
	Value* Codegen() {
		printf("FloatVal::Codegen()\n");
		return nullptr;
	}

	float value;

	virtual std::string string() {
		std::stringstream ss;
		ss << value;
		ss << "(float)" << value;
		return ss.str();
	}

	FloatVal();
	FloatVal(float val) : value(val) {} // parses a string into its value.
};

class DoubleVal : public BaseVal {
public:
	Value* Codegen() {
		printf("DoubleVal::Codegen()\n");
		return nullptr;
	}

	double value;

	virtual std::string string() {
		std::stringstream ss;
		ss << "(double)" << value;
		return ss.str();
	}

	DoubleVal();
	DoubleVal(double val) : value(val) {} // parses a string into its value.
};

#endif 