#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>

class Statement; 
class Block;

// Base 
class Statement { }; 
class Expression { }; 

class Block { 
public: 
	std::vector<Statement *> statements;  
}; 

class FunctionStatement : public Statement {
public:
	std::string name; 
}; 

class UIntVal : public Expression {
public:
	uint64_t value; 
	uint8_t size; 

	UIntVal() { }
	UIntVal(uint64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class IntVal : public Expression {
public:
	int64_t value; 
	uint8_t size; 

	IntVal() { }
	IntVal(int64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class FloatVal : public Expression {
public:
	float value; 

	FloatVal();
	FloatVal(float val) : value(val) {} // parses a string into its value.
};

class DoubleVal : public Expression {
public:
	double value; 

	DoubleVal();
	DoubleVal(double val) : value(val) {} // parses a string into its value.
};

class ValFactory {
public:
	std::string value; 
	std::string size;

	Expression *produce();	
};

#endif 