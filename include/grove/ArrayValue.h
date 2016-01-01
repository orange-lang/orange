/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

class ArrayValue : public Expression
{
private:
	std::vector<Expression *> m_elements;
public:
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	std::vector<Expression *> getElements() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool hasPointer() const override;
	
	virtual llvm::Value* getPointer() const override;
	virtual llvm::Value* getValue() const override;
	virtual bool transferrable() const override;
	
	/// Returns whether or not all of the expressions are constant values.
	virtual bool isConstant() const override;
	
	ArrayValue(std::vector<Expression *> elements);
	ArrayValue(const ArrayValue& other);
};