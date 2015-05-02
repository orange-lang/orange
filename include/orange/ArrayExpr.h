/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ARRAY_EXPR_H__
#define __ORANGE_ARRAY_EXPR_H__

#include "AST.h"

/**
 * ArrayExpr is the actual array structure containing 
 * a list of n elements. For example, in the code 
 * 		arr = [0, 1, 2]
 * [0, 1, 2] is the ArrayExpr.
 */
class ArrayExpr : public Expression {
private:
	ArgList m_elements; 
public:
	virtual std::string getClass() { return "ArrayExpr"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual AnyType* getType();

	virtual void resolve();

	/**
	 * Returns whether or not all the elements of the array 
	 * are constants or not.
	 * @return True if all the elements of the array are constant, false otherwise.
	 */
	virtual bool isConstant();

	virtual bool returnsPtr() { return true; }

	ArrayExpr(ArgList elements);
};

#endif 