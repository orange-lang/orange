#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <map>

#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/PassManager.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/Scalar.h"
using namespace llvm;

Type *getType(std::string typeStr);

class Symobj {
private:
	Value *m_value = nullptr;
	Type *m_type = nullptr; 
public:
	bool isSigned = false;
	bool isFunction = false;
	
	Value *getValue() const;
	Type *getType() const;  

	// Set value with a non-null object will 
	// also set type to the type of value. 
	void setValue(Value *v);

	// If m_value is not null, then calling this will have no effect.  
	void setType(Type *t);

	Symobj() { };
	Symobj(Value *v) { setValue(v); }
	Symobj(Type *t) { setType(t); }
}; 

class SymTable {
public:
	SymTable *parent = nullptr; 
	std::map< std::string, Symobj* > objs;
	
	// If Symobj doesn't exist, creates one. 
	void create(std::string name);
	
	Symobj* find(std::string name);
};

class ArgExpr;
class Expression;

typedef std::vector<ArgExpr *> ArgList;
typedef std::vector<Expression *> ExprList;

class Statement;
class Block;

// Base
class Statement {
public:
	virtual Value* Codegen() { return nullptr; }
	virtual std::string string() { return ""; }
};

class Expression : public Statement { 
public:
	virtual Type *getType() { return Type::getVoidTy(getGlobalContext()); }
};

class Block {
public:
	Value* Codegen();

	std::vector<Statement *> statements;

	SymTable *symtab;

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
	Value* Codegen() {
		printf("ArgExpr::Codegen()\n");
		return nullptr;
	}

	std::string type;
	std::string name;
	bool isSigned = false;

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
	Value* Codegen();

	std::string name;
	ArgList *args;
	Block *body;

	Type* getReturnType();

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
	Value* Codegen();

	Type *getType() { 
		printf("BinOpExpr::getType()\n");
		return nullptr; 
	}


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
	Value* Codegen();
	Type *getType();

	std::string name;

	virtual std::string string() {
		return name;
	}


	VarExpr(std::string name) : name(name) { }
};

class FuncCallExpr : public Expression {
public:
	Value* Codegen();

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
	Value* Codegen();

	Expression *expr;

	virtual std::string string() {
		return "RETURN " + expr->string();
	}

	ReturnExpr(Expression *expr) : expr(expr) {}
};

class BaseVal : public Expression { };

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

class ValFactory {
public:
	std::string value;
	std::string size;

	BaseVal *produce();
};

class CodeGenerator {
public:
	static std::string outputFile;
	static bool outputAssembly;

	static Module *TheModule;
	static IRBuilder<> Builder;
	static FunctionPassManager *TheFPM;
	
	static SymTable* Symtab;
	
	static void init();
	static void Generate(Block *globalBlock);
};

#endif
