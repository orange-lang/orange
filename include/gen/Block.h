#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "AST.h"

class SymTable;

class Block {
public:
	Value* Codegen();

	std::vector<Statement *> statements;
	Type* getReturnType();

	bool resolved = false;
	void resolve();

	SymTable *symtab;

	virtual std::string string() {
		std::stringstream ss;
		for (Statement *s : statements) {
			ss << s->string() << std::endl;
		}
		return ss.str();
	}
};

#endif 