/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_EXPLICIT_DECL_STMT_H__
#define __ORANGE_EXPLICIT_DECL_STMT_H__

#include "AST.h"

class VarExpr;

class ExplicitDeclStmt : public Statement {
private:
	Expression* m_expr = nullptr; 
	VarExpr* m_var = nullptr;
public:
	virtual std::string getClass() { return "ExplicitDeclStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual AnyType* getType();

	virtual bool isSigned();

	virtual void resolve();

	virtual std::string string();

	ExplicitDeclStmt(VarExpr* var);
	ExplicitDeclStmt(VarExpr* var, Expression* value);
}; 

#endif 