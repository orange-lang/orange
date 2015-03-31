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
#include "AnyType.h"

class FunctionStmt : public Block {
private:
	std::string m_name; 

	bool m_isVarArg = false; 

	// TODO: clones of this function should be LinkOnceODRLinkage.
	llvm::GlobalValue::LinkageTypes m_linkageType = Function::ExternalLinkage;

	AnyType* m_type = nullptr;

	/**
	 * Indicates the exit block of the function to jump to when returning a value.
	 */
	BasicBlock* m_blockEnd = nullptr; 

	/**
	 * Indicates the return value of the function, if any.
	 */
	Value* m_retVal = nullptr;
public:
	virtual std::string getClass() { return "FunctionStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual Type* getType();

	/** 
	 * Gets the exit block of the function to jump to when returning a value.
	 */
	BasicBlock* getBlockEnd() const { return m_blockEnd; }

	/**
	 * Gets the return value of the function. This value will be nullptr 
	 * if the function returns void.
	 */
	Value* getRetVal() const { return m_retVal; }

	/** 
	 * Gets the parent symbol table, if there is one. 
	 * If there is a parent symbol table, adds this to the 
	 * table.
	 */
	virtual void resolve();

	FunctionStmt(std::string name, SymTable* symtab);
	FunctionStmt(std::string name, AnyType* type, SymTable* symtab);

};

#endif 