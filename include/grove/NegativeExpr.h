/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Expression.h"

class NegativeExpr : public Expression {
private:
	Expression* m_expr = nullptr;
public:
	Expression* getExpression() const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	NegativeExpr(Expression* expr);
	NegativeExpr(const NegativeExpr& other);
};
