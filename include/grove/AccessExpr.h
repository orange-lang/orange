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
#include "HintProvider.h"

class AccessExpr : public Expression, public Accessible, public HintProvider
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
	
	virtual bool hasPointer() const override;
	virtual llvm::Value* getPointer() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool isAccessible() const override;
	
	virtual bool providesHint() const override;
	virtual CodeBase* getHint() const override;
	
	virtual Expression* access(OString name, const ASTNode* hint) const override;
	
	AccessExpr(Expression* LHS, OString name);
};