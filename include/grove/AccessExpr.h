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

class AccessExpr : public Expression, public Accessible
{
private:
	Expression* m_LHS = nullptr;
	std::string m_name;
	
	Expression* m_accessed = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	Expression* getLHS() const;
	std::string getName() const;
	Expression* getAccessed() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(std::string name, Type* hint) const override;
	
	AccessExpr(Expression* LHS, std::string name);
};