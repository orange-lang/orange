/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <map>

#include "Block.h"
#include "Named.h"
#include "TypeProvider.h"
#include "Accessible.h"
#include "Protectable.h"
#include "Genericable.h"

class MemberVarDecl;
class ClassMethod;
class Constructor;
class ReferenceType;

/**
 * Represents a class declaration.
 */
class ClassDecl : public Block, public Named, public Genericable,
	public TypeProvider, public Accessible, public Protectable
{
private:
	/// The Initializer for this class.
	Constructor* m_initializer = nullptr;
	
protected:
	ReferenceType* m_parent_ref = nullptr;
	ClassDecl* m_parent_class = nullptr;
	
	Constructor* createCtor(ClassMethod* method);
	
	std::map<ClassMethod*, Constructor*> m_ctor_map;
	
	/// Gets the Initializer used to initialize default values.
	Constructor* getInitializer();
public:
	Constructor* getCtorForMethod(ClassMethod* method);
	
	virtual bool usableFrom(const ASTNode* from) const override;
	
  	virtual ProtectionLevel defaultProtectionLevel() const override;
	
	virtual ASTNode* copy() const override;
	
	virtual void initialize() override;
	virtual void findDependencies() override;
	virtual void resolve() override;
	virtual void prebuild() override;
	virtual void build() override;
	
	virtual bool matchesType(const Orange::Type* other) const override;
	
	virtual bool isAccessible() const override;
	virtual Expression* access(OString name, const ASTNode* hint)
		const override;
	
	Expression* accessRegular(OString name, const ASTNode* hint)
		const;
	
	virtual bool isGeneric() const override;
	virtual Genericable* createInstance(const Orange::Type* type) override;
	
	std::vector<MemberVarDecl*> getMembers() const;
	std::vector<ClassMethod*> getMethods() const;
	
	/// Returns all generic members: members that do not have initial
	/// values and depend on a generic parameter at least once.
	std::vector<MemberVarDecl*> getGenericMembers() const;
	
	/// Gets methods where the name is equal to the class name
	std::vector<ClassMethod*> getCtors() const;
	
	/// Gets a type to use to refer to this class.
	/// Returns var if the class is generic.
	Orange::Type* getRefTy() const;
	
	ClassDecl* getParentClass() const;
	
	bool hasDefaultCtor() const;
	
	ClassMethod* getDefaultCtor() const;
	
	bool hasMethod(const OString& name) const;
	
	bool hasMember(const OString& name) const;
	
	MemberVarDecl* getMember(const OString& name) const;
	
	virtual bool hasNamed(OString name, const ASTNode* limit,
						  SearchSettings settings) const override;
	
	virtual Named* getNamed(OString name, const Orange::Type* type,
							const ASTNode* from, SearchSettings settings)
    	const override;
	
	virtual std::vector<Named *> getAllNamed(OString name, const ASTNode* from)
    	const override;
	
	ClassDecl(OString name, ReferenceType* parentReference);
	ClassDecl(const ClassDecl& other);
};