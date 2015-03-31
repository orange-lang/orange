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
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/Scalar.h"

#ifdef DEBUG
#define DEBUG_MSG(str) std::cout << "DEBUG: " << str << std::endl;
#else 
#define DEBUG_MSG(str) ;
#endif 

using namespace llvm;

Type *getType(std::string typeStr);

class ArgExpr;
class Expression;

typedef std::vector<Expression *> ExprList;

class Statement;
class Block;
class BaseVal;

class ArgList : public std::vector<ArgExpr *>  {
public:
	bool isVarArg = false;

	ArgList *clone();
};

class ASTNode {
public:
	virtual std::string getClass() { return "Root"; }
	virtual Value* Codegen() { return nullptr; }	
	virtual ASTNode* clone() { return new ASTNode(); }
	virtual std::string string() { return ""; }
	virtual Type *getType() { return Type::getVoidTy(getGlobalContext()); }
	virtual bool returnsPtr() { return false; }

	bool resolved = false;
	
	// any function that implements resolve can only 
	// be resolved once 
	virtual void resolve() { 
		if (resolved)
			return; 
		resolved = true; 
	};

	virtual ~ASTNode() { };
};

// Base
class Statement : public ASTNode {
public:
	virtual std::string getClass() { return "Statement"; }
};


class Expression : public ASTNode { 
public:
	virtual std::string getClass() { return "Expression"; }
	virtual bool isSigned() { return false; }
	virtual bool isConstant() { return true; } 
};

Value *replace(Value *del, Value *v);

#endif
