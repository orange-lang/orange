/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __FUNCTION_STATEMENT_H__
#define __FUNCTION_STATEMENT_H__
#include "AST.h"
#include "ArgExpr.h"
#include "Block.h"
#include "Symtab.h"

class FunctionStatement : public Statement {
private:
	std::vector<FunctionStatement *> clones;
	bool isClone = false;
public:
	virtual std::string getClass() { return "FunctionStatement"; }

	Value* Codegen();

	std::vector<FunctionStatement *> templated; 

	std::string name;
	ArgList *args;
	Block *body;
	AnyType *returnType = nullptr;

	void resolve();

	virtual std::string string();

	virtual Statement* clone() { 
		std::string* cloned_name = new std::string(name);
		FunctionStatement* ret = new FunctionStatement(cloned_name, args->clone(), body->clone());
		delete cloned_name; 
		return ret; 
	}

	std::string getTemplatedInstance(ExprList *callArgs, bool forceExporting = false);

	FunctionStatement(std::string* name, ArgList *args, Block *body);

	~FunctionStatement();
};

#endif 