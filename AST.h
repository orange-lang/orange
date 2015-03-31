#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>

class ArgExpr; 
class Expression; 

typedef std::vector<ArgExpr *> ArgList;
typedef std::vector<Expression *> ExprList; 

class Statement; 
class Block;

// Base 
class Statement { }; 
class Expression { }; 

class Block { 
public: 
	std::vector<Statement *> statements;  

	std::string string() { return "BLOCK PLACEHOLDER"; }
}; 

class ArgExpr : public Statement {
public:
	std::string type; 
	std::string name; 

	ArgExpr(std::string* type, std::string* name);
};

class FunctionStatement : public Statement {
public:
	std::string name; 
	ArgList *args;
	Block *body;

	FunctionStatement(std::string* name, ArgList *args, Block *body);
}; 

class BinOpExpr : public Expression { 
public:
	Expression *LHS; 
	int op;
	Expression *RHS; 

	BinOpExpr(Expression *LHS, int op, Expression *RHS);
};

class VarExpr : public Expression { 
public:
	std::string name;

	VarExpr(std::string name) : name(name) { }
};

class FuncCallExpr : public Expression {
public:
	std::string name; 
	ExprList *args;

	FuncCallExpr(std::string name, ExprList *args) : name(name), args(args) {}
};

class ReturnExpr : public Expression {
public:
	Expression *expr;
	ReturnExpr(Expression *expr) : expr(expr) {}
};

class BaseVal : public Expression { };

class UIntVal : public BaseVal {
public:
	uint64_t value; 
	uint8_t size; 

	UIntVal() { }
	UIntVal(uint64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class IntVal : public BaseVal {
public:
	int64_t value; 
	uint8_t size; 

	IntVal() { }
	IntVal(int64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class FloatVal : public BaseVal {
public:
	float value; 

	FloatVal();
	FloatVal(float val) : value(val) {} // parses a string into its value.
};

class DoubleVal : public BaseVal {
public:
	double value; 

	DoubleVal();
	DoubleVal(double val) : value(val) {} // parses a string into its value.
};

class ValFactory {
public:
	std::string value; 
	std::string size;

	BaseVal *produce();	
};

#endif 