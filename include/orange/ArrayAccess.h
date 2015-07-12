/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ARRAY_ACCESS_H__
#define __ORANGE_ARRAY_ACCESS_H__

#include "AST.h"
#include "VarExpr.h"

class ArrayAccess : public Expression {
private:
	Expression* m_variable; 
	Expression* m_idx; 
public:
	virtual std::string getClass() { return "ArrayAccess"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual void resolve();

	virtual bool returnsPtr() { return true; }

	/**
	 * Returns the variable assigned to this ArrayAccess expr. 
	 * For example, if the expr is a[5], the variable is a.
	 * @return The variable component of this expression. 
	 */
	virtual Expression* variable() const; 

	/**
	 * Returns the index assigned to this ArrayAccess expr.
	 * For example, if the expr is a[5], the idx is 5. 
	 * @return The index component of this expression.
	 */
	virtual Expression* idx() const;

	/**
	 * Constructs a new ArrayAccess expression from a variable 
	 * and an index. 
	 * @param variable The variable to use in the expression. It must be an array.
	 * @param idx The index to access the element in the variable. 
	 */
	ArrayAccess(Expression* variable, Expression* idx);
};

#endif 