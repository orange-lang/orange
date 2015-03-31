/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_RETURN_STMT_H__
#define __ORANGE_RETURN_STMT_H__

#include "AST.h"

class ReturnStmt : public Statement {
private:
	Expression* m_expr; 
public:
	virtual std::string getClass() { return "ReturnStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone() {
		ReturnStmt* cloned = m_expr ? new ReturnStmt((Expression *)m_expr->clone()) : new ReturnStmt();
		return cloned; 
	}

	virtual Type* getType();

	virtual std::string string() {
		if (m_expr)
			return "RETURN " + m_expr->string();
		else 
			return "RETURN";
	}

	virtual void resolve();

	ReturnStmt() {}
	ReturnStmt(Expression* expr) : m_expr(expr) {};
}; 

#endif 