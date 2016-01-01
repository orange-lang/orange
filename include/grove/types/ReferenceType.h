/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "NodeType.h"
#include "../Typed.h"
#include "../Accessible.h"

class ReferenceType : public NodeType, public Typed, public Accessible
{
protected:
	OString m_name;
	ASTNode* m_reference = nullptr;
	
	/// True if constructed with a ref type.
	bool m_sticky_ref_type = false;
	
	void findReference();
public:
	OString getName() const;
	
	virtual Module* getModule() const override;
	
	virtual const Type* getComparisonTy() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	ASTNode* getReference() const;
	
	virtual bool isAccessible() const override;
	
	virtual Expression* access(OString name, const ASTNode* hint) const override;
	
	virtual void initialize() override;
	virtual void findDependencies() override;
	virtual void resolve() override;
	
	virtual bool canInitializeVar() const override;
	virtual Expression* initializeVar() const override;
	
	virtual ASTNode* copy() const override;
	virtual const Type* copyType() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	void setRefType(const Type* ty);
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	ReferenceType(OString name);
	ReferenceType(const ASTNode* reference);
	ReferenceType(const ASTNode* reference, const Type* refType);
};