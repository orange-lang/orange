/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

class ReferenceExpr : public Expression
{
private:
	Expression* m_expression = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	Expression* getExpression() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	ReferenceExpr(Expression* expr);
	ReferenceExpr(const ReferenceExpr& other);
};