#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "AST.h"
#include "Symtab.h"

class SymTable;

class Block {
public:
	Value* Codegen();

	std::vector<ASTNode *> statements;
	Type* getReturnType();
	Type* getLastStatementType();

	bool hasReturnStatement();
	bool hasJmpInstr();

	bool resolved = false;
	void resolve();

	SymTable *symtab;

	virtual Block* clone();

	virtual std::string string();

	virtual ~Block();
};

#endif 