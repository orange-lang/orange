/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Block.h"
#include "Named.h"
#include "Typed.h"
#include "TypeProvider.h"
#include "Accessible.h"
#include "Protectable.h"

class MemberVarDecl;
class ClassMethod;

/**
 * Represents a class declaration.
 */
class ClassDecl : public Block, public Named, public Typed,
	public TypeProvider, public Accessible, public Protectable
{
protected:
	void createCtor(ClassMethod* method) const;
public:
	virtual bool usableFrom(const ASTNode* from) const override;
	
  	virtual ProtectionLevel defaultProtectionLevel() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual bool matchesType(const Type* other) const override;
	
	virtual bool isAccessible() const override;
	virtual Expression* access(OString name, const ASTNode* hint)
		const override;
	
	std::vector<MemberVarDecl*> getMembers() const;
	std::vector<ClassMethod*> getMethods() const;
	
	/// Gets methods where the name is equal to the class name
	std::vector<ClassMethod*> getCtors() const;
	
	bool hasDefaultCtor() const;
	
	virtual void findDependencies() override;
	
	bool hasMethod(const OString& name) const;
	
	bool hasMember(const OString& name) const;
	
	MemberVarDecl* getMember(const OString& name) const;
	
	ClassDecl(OString name);
	ClassDecl(const ClassDecl& other);
};