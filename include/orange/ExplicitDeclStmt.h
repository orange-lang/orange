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
#include "DeclPair.h"

class VarExpr;

class ExplicitDeclStmt : public Statement {
private:
	Expression* m_expr = nullptr; 
	VarExpr* m_var = nullptr;

	struct DeclPairInternal {
		VarExpr* var; 
		Expression* val; 

		DeclPairInternal() {}
		DeclPairInternal(VarExpr* var, Expression* val) : var(var), val(val) {}
	};

	std::vector<DeclPairInternal> m_extras;

	Value* CodegenPair(VarExpr* var, Expression* expr);
public:
	virtual std::string getClass() { return "ExplicitDeclStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual OrangeTy* getType();

	virtual bool isSigned();

	virtual void resolve();

	virtual std::string string();

	ExplicitDeclStmt(VarExpr* var);
	ExplicitDeclStmt(VarExpr* var, std::vector<DeclPair> extras);
	ExplicitDeclStmt(VarExpr* var, Expression* value);
	ExplicitDeclStmt(VarExpr* var, Expression* value, std::vector<DeclPair> extras);
}; 

#endif 