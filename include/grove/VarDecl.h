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
#include "Named.h"
#include "Valued.h"
#include "Accessible.h"

class Expression;

/**
 * VarDecl is a statement that represents a variable declaration. 
 * It is named, typed, and valued. Its value is the variable created.
 */
class VarDecl : public Statement, public Named, public Typed, public Valued,
	public Accessible
{
private:
	Expression* m_expr = nullptr;
	
	/// Returns whether or not to allocate a variable.
	bool allocateVariable();
public:
	virtual llvm::Value* getValue() const override;
	virtual llvm::Value* getPointer() const override;
	virtual bool hasPointer() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	virtual Expression* access(OString name, const ASTNode* hint) const override;
	
	Expression* getExpression() const;
	
	VarDecl(Type* type, OString name, Expression* expression);
};