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