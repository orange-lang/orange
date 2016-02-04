/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Statement.h"
#include "Typed.h"

class Expression;

class ReturnStmt : public Statement, public Typed {
private:
	Expression* m_expr = nullptr;
public:
	/// Get the expression that the return statement returns.
	Expression* getExpression();
	
	/// Returns whether or not the return statement has an expression.
	bool hasExpression();
	
	virtual bool isTerminator() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	ReturnStmt(Expression* expression);
	ReturnStmt(const ReturnStmt& other);
};
