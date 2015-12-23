/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

class IncrementExpr : public Expression
{
private:
	Expression* m_expr = nullptr;
	bool m_preincrement = false;
	int m_delta = 0;
public:
	Expression* getExpression() const;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	int getDelta() const;
	
	bool isPreIncrement() const;
	bool isPostIncrement() const;
	
	IncrementExpr(Expression* expr, int delta, bool preincrement);
	IncrementExpr(const IncrementExpr& other);
};