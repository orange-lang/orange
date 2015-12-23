/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Expression.h"

class TernaryExpr : public Expression
{
private:
	Expression* m_condition = nullptr;
	Expression* m_true_val = nullptr;
	Expression* m_false_val = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	Expression* getCondition() const;
	Expression* getTrueVal() const;
	Expression* getFalseVal() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	TernaryExpr(Expression* condition, Expression* trueval,
				Expression* falseval);
	TernaryExpr(const TernaryExpr& other);
};