/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Expression.h"
#include "Accessible.h"

class Valued;

/**
 * IDReference is a class that can refer to any ID by name.
 */
class IDReference : public Expression, public Accessible {
private:
	OString m_name;
	
protected:
	/// Find the named node in the block.
	Valued* findNode() const;
	
	Valued* m_node = nullptr;
public:
	virtual llvm::Value* getPointer() const override;
	
	virtual bool hasPointer() const override;
	
	virtual llvm::Value* getValue() const override;
	
	virtual llvm::Value* getSize() const override;
	
	/// Gets the name that this node is referring to.
	OString getName() const;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, Type* hint) const override;
	
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	
	virtual ASTNode* copy() const override;
	
	IDReference(OString name);
};
