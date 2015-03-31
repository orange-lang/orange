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
#include "AnyType.h"

class VarExpr : public Expression {
private:
	std::string m_name;

	bool m_locked = false;
protected: 
	/** 
	 * Indicates whether or not this variable is a signed
	 * type.
	 */
	bool m_signed = false;

	/** 
	 * Determines the type of the variable.
	 */
	AnyType* m_type = nullptr; 
public:
	virtual std::string getClass() { return "VarExpr"; }

	virtual bool isLocked() const { return m_locked; }

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		VarExpr* ret = new VarExpr(m_name);
		ret->m_locked = m_locked; 
		ret->m_signed = m_signed; 
		return ret;
	}

	virtual std::string string();

	virtual AnyType* getType();

	virtual AnyType* type() const { return m_type; }

	virtual void setType(AnyType* type) { m_type = type; }

	virtual Value* getValue();

	virtual void resolve();

	virtual bool isSigned() { return m_signed; }

	virtual void setSigned(bool signed_var); 

	virtual void setValue(Value* value);

	virtual void setValueTo(Value* value);

	/**
	 * Tries to create this variable in the symbol table.
	 */
	virtual void create(bool throwError = true); 

	// variables are *never* constant expressions.
	virtual bool isConstant() { return false; }

	virtual bool returnsPtr() { return true; }

	virtual std::string name() const { return m_name; }

	VarExpr(std::string name); 

	/** 
	 * Creates a variable with a locked down type.
	 */
	VarExpr(std::string name, AnyType* type);
};

#endif 