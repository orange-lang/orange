/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Statement.h"
#include "Typed.h"
#include "Named.h"
#include "Valued.h"

class Expression;

/**
 * VarDecl is a statement that represents a variable declaration. 
 * It is named, typed, and valued. Its value is the variable created.
 */
class VarDecl : public Statement, public Named, public Typed, public Valued
{
private:
	Expression* m_expr = nullptr;
public:
	virtual llvm::Value* getValue() const override;
	virtual llvm::Value* getPointer() const override;
	virtual bool hasPointer() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	Expression* getExpression() const;
	
	VarDecl(Type* type, OString name, Expression* expression);
};