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
 * CastExpr casts a node's type to another
 */
class CastExpr : public Expression
{
private:
	Expression* m_expression;
public:
	virtual ASTNode* copy() const override;
	
	Expression* getExpression() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	CastExpr(Type* ty, Expression* expr);
};