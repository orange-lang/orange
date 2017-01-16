/*
 ** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include "Expression.h"

/**
 * Gets the size of an expression or a type
 */
class SizeofExpr : public Expression
{
private:
	Expression* m_expression_arg = nullptr;
	Type* m_type_arg = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	/// Gets the expression, if any, to get the size of.
	Expression* getExpressionArg() const;
	
	/// Gets the type, if any, to get the size of.
	Type* getTypeArg() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	SizeofExpr(Type* typeArg);
	SizeofExpr(Expression* expr);
};