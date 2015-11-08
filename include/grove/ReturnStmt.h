/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Statement.h"
#include "Typed.h"

class ReturnStmt : public Statement, public Typed {
private:
	ASTNode* m_expr = nullptr;
public:
	/// Get the expression that the return statement returns.
	ASTNode* getExpression();
	
	/// Returns whether or not the return statement has an expression.
	bool hasExpression();
	
	virtual void build();
	
	ReturnStmt(ASTNode* parent, ASTNode* expression);
};
