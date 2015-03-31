/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_FUNCTION_H__
#define __ORANGE_FUNCTION_H__
#include "AST.h"
#include "Block.h"

class FunctionStmt : public Block {
private:
	std::string m_name; 

	bool m_isVarArg = false; 

	// TODO: clones of this function should be LinkOnceODRLinkage.
	llvm::GlobalValue::LinkageTypes m_linkageType = Function::ExternalLinkage;
public:
	virtual std::string getClass() { return "FunctionStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	/** 
	 * Gets the parent symbol table, if there is one. 
	 * If there is a parent symbol table, adds this to the 
	 * table.
	 */
	virtual void resolve();

	FunctionStmt(std::string name, SymTable* symtab);
};

#endif 