#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>
#include <sstream>

class ArgExpr; 
class Expression; 

typedef std::vector<ArgExpr *> ArgList;
typedef std::vector<Expression *> ExprList; 

class Statement; 
class Block;

// Base 
class Statement { 
public:
	virtual std::string string() { return ""; } 
}; 

class Expression { 
public:
	virtual std::string string() { return ""; } 
}; 

class Block { 
public: 
	std::vector<Statement *> statements;  

	std::string string() { 	
		std::stringstream ss;
		for (Statement *s : statements) {
			ss << s->string() << std::endl;
		}
		return ss.str();
	}
}; 

class ArgExpr : public Statement {
public:
	std::string type; 
	std::string name; 

	virtual std::string string() { 
		std::stringstream ss; 
		if (type != "") {
			ss << type << " ";
		}
		ss << name; 
		return ss.str();
	}

	ArgExpr(std::string* type, std::string* name);
};

class FunctionStatement : public Statement {
public:
	std::string name; 
	ArgList *args;
	Block *body;

	virtual std::string string() { 
		std::stringstream ss;
		ss << name << "( ";
		for (int i = 0; i < args->size(); i++) {
			ss << (*args)[i]->string() << " ";
			if (i + 1 != args->size()) 
				ss << ", ";
		} 
		ss << "):\n";
	
		for (Statement *s : body->statements) {
			ss << "\t" << s->string() << std::endl;
		}

		return ss.str();
	} 

	FunctionStatement(std::string* name, ArgList *args, Block *body);
}; 

class BinOpExpr : public Expression { 
public:
	Expression *LHS; 
	char op;
	Expression *RHS; 

	virtual std::string string() { 
		std::stringstream ss;
		ss << "( " << LHS->string() << " " << op << " " << RHS->string() << " )";
		return ss.str();
	}

	BinOpExpr(Expression *LHS, char op, Expression *RHS);
};

class VarExpr : public Expression { 
public:
	std::string name;

	virtual std::string string() { 
		return name; 
	}


	VarExpr(std::string name) : name(name) { }
};

class FuncCallExpr : public Expression {
public:
	std::string name; 
	ExprList *args;

	virtual std::string string() { 
		std::stringstream ss;
		ss << name << "( ";
		for (int i = 0; i < args->size(); i++) {
			ss << (*args)[i]->string() << " ";
			if (i + 1 != args->size()) 
				ss << ", ";
		} 
		ss << ")";
	
		return ss.str();
	}

	FuncCallExpr(std::string name, ExprList *args) : name(name), args(args) {}
};

class ReturnExpr : public Expression {
public:
	Expression *expr;

	virtual std::string string() { 
		return "RETURN " + expr->string();
	}

	ReturnExpr(Expression *expr) : expr(expr) {}
};

class BaseVal : public Expression { };

class UIntVal : public BaseVal {
public:
	uint64_t value; 
	uint8_t size; 

	virtual std::string string() { 
		std::stringstream ss;
		ss << "(uint" << (uint64_t)size << ")" << value;
		return ss.str();
	}	

	UIntVal() { }
	UIntVal(uint64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class IntVal : public BaseVal {
public:
	int64_t value; 
	uint8_t size; 

	virtual std::string string() { 
		std::stringstream ss;
		ss << "(int" << (uint64_t)size << ")" << value;
		return ss.str();
	}	

	IntVal() { }
	IntVal(int64_t val, uint8_t size) : value(val), size(size) {} // parses a string into its value. 
};

class FloatVal : public BaseVal {
public:
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
	double value; 

	virtual std::string string() { 
		std::stringstream ss;
		ss << "(double)" << value;
		return ss.str();
	}	

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