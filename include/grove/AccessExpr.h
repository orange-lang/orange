/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"
#include "Accessible.h"
#include "OString.h"

class AccessExpr : public Expression, public Accessible
{
private:
	Expression* m_LHS = nullptr;
	OString m_name;
	
	Expression* m_accessed = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	Expression* getLHS() const;
	OString getName() const;
	Expression* getAccessed() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, Type* hint) const override;
	
	AccessExpr(Expression* LHS, OString name);
};