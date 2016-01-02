/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"
#include "../OString.h"

namespace Orange { class ClassType; }

class ClassDecl;

class Orange::ClassType : public Orange::Type
{
private:
	std::vector<const Type *> m_members;
	ClassDecl* m_class = nullptr;
	
	bool m_opaque = false;
protected:
	// Creates a ClassType with members
	ClassType(ClassDecl* the_class, std::vector<const Type *> members);
	
	// Creates an opaque ClassType where the members can be specified
	// later
	ClassType(ClassDecl* the_class);
public:
	static std::string getSignature(const ClassDecl* name,
									const std::vector<const Type *> members,
									bool opaque);
	
	virtual bool isClassTy() const override;
	virtual bool isAggTy() const override;
	
	virtual bool hasReference() const override;
	virtual ASTNode* getReference() const override;
	
	bool isOpaque() const;
	
	ClassDecl* getClass() const;
	
	virtual const Type* replaceMember(const Type* member, const Type* with)
		const override;
	
	virtual std::vector<const Type*> getMemberTys() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual const Type* copyType() const override;
	
	/// Specifies the members of an opaque class.
	/// Fails if this type isn't opaque.
	void specifyMembers(std::vector<const Type *> members);
	
	static ClassType* get(Module* mod, ClassDecl* the_class);
	
	static ClassType* get(Module* mod, ClassDecl* the_class,
						  std::vector<const Type *> members);
};