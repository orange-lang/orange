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

class AnyType {
public:
	std::string type; 
	int numPointers = 0; 

	Type *getType();

	AnyType(std::string *type, int numPointers) : type(*type), numPointers(numPointers) {}
};


class StrVal : public Expression {
public:
	std::string value; 

	virtual Type *getType() { return Type::getInt8PtrTy(getGlobalContext()); }

	Value* Codegen();

	StrVal(std::string v);
};

class BaseVal : public Expression { };

class ValFactory {
public:
	std::string value;
	std::string size;

	BaseVal *produce();
};

#endif
