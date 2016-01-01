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

class Valued;

/**
 * NodeReference is a class that can refer to any ID by name.
 */
class NodeReference : public Expression, public Accessible {
private:
	ASTNode* m_node = nullptr;
protected:
	void setNode(ASTNode* node);
	
	NodeReference();
public:
	const Valued* nodeAsValued() const;
	
	const ASTNode* getNode() const;
	
	virtual llvm::Value* getPointer() const override;
	
	virtual bool hasPointer() const override;
	
	virtual bool transferrable() const override;
	
	virtual llvm::Value* getValue() const override;
	
	virtual llvm::Value* getSize() const override;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, const ASTNode* hint) const override;
	
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	NodeReference(ASTNode* node);
	NodeReference(const NodeReference& other);
};
