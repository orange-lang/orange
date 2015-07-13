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
#include "VarExpr.h"

class ParamList : public std::vector<VarExpr *> {
private:
	bool m_var_arg = false;
public:
	bool varArg() const { return m_var_arg; }
	void setVarArg(bool isVarArg) { m_var_arg = isVarArg; }
};

class FunctionStmt : public Block {
private:
	std::string m_name; 
	std::string m_orig_name;

	bool m_isVarArg = false; 

	// TODO: clones of this function should be LinkOnceODRLinkage.
	llvm::GlobalValue::LinkageTypes m_linkageType = Function::ExternalLinkage;

	/**
	 * Indicates the exit block of the function to jump to when returning a value.
	 */
	BasicBlock* m_blockEnd = nullptr; 

	/**
	 * Indicates the return value of the function, if any.
	 */
	Value* m_retVal = nullptr;
	
	ParamList m_parameters;

	std::vector<FunctionStmt*> m_clones;

	std::string getShortName(OrangeTy* t);

	/** 
	 * Set to true when the name has been mangled.
	 */
	bool m_mangled = false;

	bool m_type_set = false;
public:
	virtual std::string getClass() { return "FunctionStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual std::string name() const { return m_name; }

	/** 
	 * FunctionStmts aren't "traditional" blocks.
	 */
	virtual bool isBlock() { return false; }


	/**
	 * Returns true if any of the functions are a void type.
	 *
	 * @return True if this is a generic function, false otherwise.
	 */
	virtual bool isGeneric();

	/**
	 * Clones are generated as separate functions and must be 
	 * named differently. Their name is always going to be 
	 * m_name + _ + (list of short names for argument types).
	 *
	 * The short names are as follows:
	 * 	b for signed int8, B for unsigned. 
	 * 	s for signed int16, S for unsigned. 
	 *	i for signed int32, I for unsigned. 
	 * 	l for signed int64, L for unsigned.
	 * 	f for float.
	 * 	d for double.
	 *	p for all pointers (uint8** would be Bpp)
	 *
	 * @returns The mangled name for a function that is not a generic.
	 */
	std::string getMangledName(ArgList args);
	std::string getMangledName(ParamList params);

	/** 
	 * Attempts to create a generic clone of this function with 
	 * arguments resolved to a specific type.
	 *
	 * @param args The list of arguments being passed to this FunctionStmt.
	 *
	 * @return The clone. May return a clone previously created if one already exists with that 
	 *	type signature.
	 */
	virtual FunctionStmt* createGenericClone(ArgList args);

	virtual FunctionStmt* getGenericClone(ArgList args);

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
	 * Creates a basic block at the end of this function.
	 * 
	 * @param name The name of the block.
	 */
	BasicBlock* createBasicBlock(std::string name);

	virtual void mapDependencies();

	virtual void initialize();

	/** 
	 * Gets the parent symbol table, if there is one. 
	 * If there is a parent symbol table, adds this to the 
	 * table.
	 */
	virtual void resolve();

	std::string dump();

	/** 
	 * If set before resolve, will disable name mangling. 
	 */
	void disableMangle() { m_mangled = true; }

	ParamList parameters() const { 
		return m_parameters; 
	} 

	FunctionStmt(std::string name, ParamList parameters, SymTable* symtab);
	FunctionStmt(std::string name, OrangeTy* type, ParamList parameters, SymTable* symtab);

};

#endif 