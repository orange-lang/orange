/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_VAR_EXPR_H__
#define __ORANGE_VAR_EXPR_H__

#include "AST.h"

class VarExpr : public Expression {
private:
	std::string m_name;

	bool m_locked = false;

	/**
	 * @return The symtab variable if it exists, or this if it doesn't.
	 */
	VarExpr* symtabVar();
protected: 
	/** 
	 * Indicates whether or not this variable is a signed
	 * type.
	 */
	bool m_signed = false;

	/**
	 * Determines whether or not the variable is const.
	 */
	bool m_constant = false;

	/**
	 * Determines whether or not it is initialized, which will happen 
	 * after running Codegen at least once if the variable is constant.
	 */
	bool m_initialized = false;
public:
	virtual std::string getClass() { return "VarExpr"; }

	virtual bool isLocked();

	virtual Value* Codegen();

	/** 
	 * Initialize our variable. If the variable is a constant, it will lock it down 
	 * so it can no longer be modified.
	 */
	virtual void initialize(); 

	virtual ASTNode* clone() {
		VarExpr* ret = new VarExpr(m_name);
		ret->m_locked = m_locked; 
		ret->m_signed = m_signed; 
		return ret;
	}

	virtual std::string string();

	virtual OrangeTy* getType();

	virtual void setType(OrangeTy* type);

	virtual Value* getValue();

	virtual void resolve();

	virtual bool isSigned() { return getType()->isSigned(); }

	virtual void setValue(Value* value);

	virtual void setValueTo(Value* value);

	/**
	 * Tries to create this variable in the symbol table.
	 */
	virtual void create(bool throwError = true); 

	/**
	 * Returns whether or not this variable exists in a parent.
	 */
	virtual bool existsInParent();

	// variables are *never* constant expressions.
	virtual bool isConstant() { return false; }

	virtual bool returnsPtr();

	virtual std::string name() const { return m_name; }

	/**
	 * Allocates this variable and sets it as its value. 
	 */
	virtual Value* allocate();

	VarExpr(std::string name); 

	/*
	 * Creates a constant variable.
	 */
	VarExpr(std::string name, bool constant);

	/** 
	 * Creates a variable with a locked down type.
	 */
	VarExpr(std::string name, OrangeTy* type);

	/** 
	 * Creates a variable with a locked down type and as a constant.
	 */
	VarExpr(std::string name, OrangeTy* type, bool constant);
};

#endif 