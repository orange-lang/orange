/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_BLOCK_H__
#define __ORANGE_BLOCK_H__

#include "AST.h"
#include "SymTable.h"

class Block : public Statement {
private:
	/**
	 * The symbol table for this Block.
	 */
	SymTable *m_symtab;
protected:
	/**
	 * Determines whether or not this block is locked,
	 * which will happen upon calling Codegen().
	 */
	bool m_locked = false;

	std::vector<ASTNode *> m_statements;

	/**
	 * Generates all of the statements.
	 */
	void generateStatements();	
public:
	virtual std::string getClass() { return "Block"; }

	/**
	 * Gets the symbol table tied to this block.
	 *
	 * @return The symbol table tied to this block.
	 */
	SymTable* symtab() const;

	/**
	 * Returns whether or not we are the root block.
	 *
	 * @return True if we are the root, false otherwise.
	 */
	bool isRoot() const;

	/**
	 * Adds a statement to the list of statements for this block.
	 * After Codegen has been called, no more statements can be 
	 * added and this function will do nothing.
	 *
	 * @param statement The statement to add to this block.
	 */
	void addStatement(ASTNode* statement); 

	/**
	 * Generates code for each statement added to this block.
	 * If a statement throws an exception during code generation,
	 * This will catch it and log it to the Runner.
	 *
	 * @return This function always returns nothing.
	 */ 
	Value* Codegen();

	/**
	 * Determines whether or not the body has a return stmt.
	 * Does not check for nested bodies. 
	 *
	 * @return True if the body has a return statement, false otherwise.
	 */
	bool hasReturn();

	/**
	 * Gets the return type from the body, if it exists.
	 * Does not check for nested bodies (e.g., if statements)
	 *
	 * @return A type if a return type exists, false otherwise.
	 */ 
	Type* returnType();

	virtual ASTNode* clone();

	virtual std::string string();

	/**
	 * This will resolve every statement added to this block.
	 */
	void resolve();

	/**
	 * Creates a block. Every block must have a symbol table attached to 
	 * it. A runtime_error will be thrown if symtab is nullptr.
	 *
	 * @param symtab The symtab for this block. Must not be null.
	 */
	Block(SymTable* symtab);
};

#endif 