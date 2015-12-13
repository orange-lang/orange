/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

class ArrayAccessExpr : public Expression
{
private:
	Expression* m_array = nullptr;
	Expression* m_idx = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	/// Gest the array that this expression is accessing.
	Expression* getArray() const;
	
	/// Gets the index of the array that this expression is accessing.
	Expression* getIndex() const;
	
	virtual bool hasPointer() const override;
	
	virtual llvm::Value* getValue() const override;
	virtual llvm::Value* getPointer() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	ArrayAccessExpr(Expression* array, Expression* idx);
};