/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_COMMA_STMT_H__
#define __ORANGE_COMMA_STMT_H__

#include "AST.h"

class CommaStmt : public Statement {
private:
	std::vector<Expression*> m_exprs;
public:
	virtual std::string getClass() { return "CommaStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual void resolve();

	virtual std::string string();

	CommaStmt(std::vector<Expression*> expressions);
}; 

#endif 