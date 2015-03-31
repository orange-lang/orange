#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "AST.h"

class SymTable;

class Block {
public:
	Value* Codegen();

	std::vector<Statement *> statements;
	Type* getReturnType();

	bool hasReturnStatement();

	bool resolved = false;
	void resolve();

	SymTable *symtab;

	virtual std::string string();
};

#endif 