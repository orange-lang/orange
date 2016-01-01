/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"
#include "Accessible.h"

class ArrayAccessExpr : public Expression, public Accessible
{
private:
	Expression* m_array = nullptr;
	Expression* m_idx = nullptr;
public:
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	/// Gest the array that this expression is accessing.
	Expression* getArray() const;
	
	/// Gets the index of the array that this expression is accessing.
	Expression* getIndex() const;
	
	virtual bool hasPointer() const override;
	
	virtual llvm::Value* getValue() const override;
	virtual llvm::Value* getPointer() const override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, const ASTNode* hint)
		const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	ArrayAccessExpr(Expression* array, Expression* idx);
	ArrayAccessExpr(const ArrayAccessExpr& other);
};