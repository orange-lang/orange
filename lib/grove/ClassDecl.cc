/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/ClassDecl.h>
#include <grove/ClassTopLevel.h>
#include <grove/MemberVarDecl.h>
#include <grove/ClassMethod.h>
#include <grove/ReturnStmt.h>
#include <grove/IDReference.h>
#include <grove/Module.h>
#include <grove/Parameter.h>
#include <grove/MemberAccess.h>
#include <grove/MethodAccess.h>
#include <grove/StaticMethodAccess.h>
#include <grove/Constructor.h>
#include <grove/ExpressionCall.h>
#include <grove/AccessExpr.h>
#include <grove/BinOpAssign.h>

#include <grove/types/VoidType.h>
#include <grove/types/VarType.h>
#include <grove/types/FutureType.h>

#include <grove/exceptions/code_error.h>
#include <grove/exceptions/already_defined_error.h>

#include <grove/types/ClassType.h>
#include <grove/types/ReferenceType.h>

#include <util/assertions.h>
#include <util/copy.h>

bool ClassDecl::usableFrom(const ASTNode *from) const
{
	return getProtectionLevel() == ProtectionLevel::PROTECTION_PUBLIC;
}

ProtectionLevel ClassDecl::defaultProtectionLevel() const
{
	return ProtectionLevel::PROTECTION_PUBLIC;
}

ASTNode* ClassDecl::copy() const
{
	return new ClassDecl(*this);
}

std::vector<MemberVarDecl *> ClassDecl::getMembers() const
{
	std::vector<MemberVarDecl *> ret;
	
	for (auto child : getChildren())
	{
		if (child->is<MemberVarDecl *>())
		{
			ret.push_back(child->as<MemberVarDecl *>());
		}
	}
	
	return ret;
}

std::vector<ClassMethod *> ClassDecl::getMethods() const
{
	std::vector<ClassMethod *> ret;
	
	for (auto child : getChildren())
	{
		if (child->is<ClassMethod *>() &&
			child->as<ClassMethod *>()->isConstructor() == false)
		{
			ret.push_back(child->as<ClassMethod *>());
		}
	}
	
	return ret;
}

std::vector<ClassMethod *> ClassDecl::getCtors() const
{
	std::vector<ClassMethod *> ret;
	
	for (auto child : getChildren())
	{
		if (child->is<ClassMethod *>() &&
			child->as<ClassMethod *>()->getName() == getName())
		{
			ret.push_back(child->as<ClassMethod *>());
		}
	}
	
	return ret;
}

ClassDecl* ClassDecl::getParentClass() const
{
	return m_parent_class;
}

bool ClassDecl::hasDefaultCtor() const
{
	auto&& ctors = getCtors();
	if (ctors.size() == 0)
	{
		return true;
	}
	
	// For each ctor, see if there's a ctor that has params that are only
	// the this parameter. 
	for (auto& ctor : ctors)
	{
		bool defaultable = true;
		
		auto&& params = ctor->getParams();
		for (auto param : params)
		{
			if (param != ctor->getThisParam())
			{
				defaultable = false;
				break;
			}
		}
		
		if (defaultable == true)
		{
			return true;
		}
	}
	
	return false;
}

Constructor* ClassDecl::getInitializer()
{
	if (m_initializer != nullptr)
	{
		return m_initializer;
	}
	
	std::vector<Parameter *> params;
	auto this_ty = getRefTy();
	params.push_back(new Parameter(this_ty->getPointerTo(), "this"));
	
	m_initializer = new Constructor(this, nullptr, "I" + getName(), params);
	m_initializer->setReturnType(Orange::VoidType::get(getModule()));
	
	m_initializer->setLocation(this->getLocation());
	
	if (getParentClass())
	{
		auto parent_initializer = getParentClass()->getInitializer();
		
		// Call the parent's initializer
		std::vector<Expression *> arg_list;
		arg_list.push_back(new IDReference("this"));
		
		auto call = new ExpressionCall(parent_initializer, arg_list);
		m_initializer->addStatement(call);
	}
	
	// The initializer needs to instantiate all of its variables that have
	// values, and call the method, if one exists.
	auto&& members = getMembers();
	for (auto& member : members)
	{
		if (member->getExpression() == nullptr)
		{
			continue;
		}
		
		// this.[member] = member->getExpression()
		
		auto this_ref = new IDReference("this");
		auto access = new AccessExpr(this_ref, member->getName());
		auto value = member->getExpression()->copy()->as<Expression *>();
		auto assign = new BinOpAssign(access, "=", value);
		
		this_ref->setLocation(member->getLocation());
		access->setLocation(member->getLocation());
		value->setLocation(member->getExpression()->getLocation());
		assign->setLocation(member->getLocation());
		
		m_initializer->addStatement(assign);
	}
	
	auto ret_stmt = new ReturnStmt(nullptr);
	
	m_initializer->addStatement(ret_stmt);
	findParent<Block *>()->addChild(m_initializer, this, 1);
	
	getModule()->process(m_initializer);
	
	return m_initializer;
}

Constructor* ClassDecl::createCtor(ClassMethod *method)
{
	assertExists(getParent(), "class has no parent!");
	
	std::vector<Parameter *> params;
	
	if (method != nullptr)
	{
		params = copyVector(method->getParams());
	}
	
	// If we don't have a method, we have to manually
	// add in the this param.
	if (method == nullptr)
	{
		auto this_ty = getRefTy();
		params.push_back(new Parameter(this_ty->getPointerTo(), "this"));
	}
	
	auto func = new Constructor(this, method, getName(), params);
	
	func->setReturnType(Orange::VoidType::get(getModule()));
	
	if (method != nullptr)
	{
		func->setLocation(method->getLocation());
	}
	else
	{
		func->setLocation(ASTNode::getLocation());
	}
	
	{
		// Call the initializer
		std::vector<Expression *> arg_list;
		arg_list.push_back(new IDReference("this"));
		
		auto call = new ExpressionCall(getInitializer(), arg_list);
		func->addStatement(call);
	}
	
	if (method != nullptr)
	{
		std::vector<Expression *> arg_list;
		
		for (auto param : params)
		{
			 arg_list.push_back(new IDReference(param->getName()));
		}
		
		func->addStatement(new ExpressionCall(method, arg_list));
	}
	
	// Return nothing.
	auto ret_stmt = new ReturnStmt(nullptr);
	
	// Add all the statements to the class.
	func->addStatement(ret_stmt);
	
	// Add the function to our parent block after this class.
	// There's never a reason to add it to our parent as well, since
	// our parent will always be the parent block.
	findParent<Block *>()->addChild(func, this, 1);
	
	// Request a resolve of our function.
	getModule()->process(func);
	
	m_ctor_map[method] = func;
	return func;
}

Constructor* ClassDecl::getCtorForMethod(ClassMethod *method)
{
	auto it = m_ctor_map.find(method);
	if (it == m_ctor_map.end())
	{
		getModule()->beginCopy();
		auto ret = createCtor(method);
		getModule()->endCopy();
		return ret;
	}
	else
	{
		return it->second;
	}
}

bool ClassDecl::hasMethod(const OString &name) const
{
	auto&& methods = getMethods();
	for (const auto& method : methods)
	{
		if (method->getName() == name)
		{
			return true;
		}
	}
	
	return false;
}

bool ClassDecl::hasMember(const OString &name) const
{
	auto&& members = getMembers();
	for (const auto& member : members)
	{
		if (member->getName() == name)
		{
			return true;
		}
	}
	
	return false;
}

MemberVarDecl* ClassDecl::getMember(const OString &name) const
{
	auto&& members = getMembers();
	for (const auto& member : members)
	{
		if (member->getName() == name)
		{
			return member;
		}
	}
	
	return nullptr;
}

void ClassDecl::initialize()
{
	if (m_parent_ref)
	{
		getModule()->initialize(m_parent_ref);
		auto ref = m_parent_ref->getReference();
		
		if (ref->is<ClassDecl *>() == false)
		{
			throw code_error(this, ref, []() -> std::string
							 {
								 return "A class can only inherit from another "
								 "class";
							 });
		}
		
		m_parent_class = ref->as<ClassDecl *>();
	}
}

void ClassDecl::findDependencies()
{
	if (getParentClass())
	{
		addDependency(getParentClass());
	}
}

void ClassDecl::resolve()
{
	// Make sure that the class's name is unique.
	SearchSettings settings;
	settings.createGeneric = false;
	settings.includeLimit = false;
	settings.filter = [this](Named* named) -> bool
	{
		if (named->is<ClassDecl *>())
		{
			auto other = named->as<ClassDecl *>();
			return other->getInstanceParent() == this;
		}
		
		return named->is<Constructor *>() == false;
	};
	
	auto named = findNamed(getName(), nullptr, settings);
	if (named != nullptr && named != this)
	{
		auto base = named->as<CodeBase *>();
		throw already_defined_error(&m_name, base, m_name, false);
	}
	
	// First, make sure that all of the statements are ClassTopLevels.
	for (auto child : getStatements())
	{
		if (child->is<ClassTopLevel *>() == false)
		{
			throw code_error(child, []() -> std::string
				{
					return "invalid child of class";
				});
		}
	}
	
	if (isGeneric())
	{
		setType(Orange::VarType::get(getModule()));
	}
	else
	{
		auto classTy = Orange::ClassType::get(getModule(), this);
		setType(classTy);
	}
	
	// Create all of our constructors.
	getModule()->beginCopy();
	
	auto ctors = getCtors();
	if (ctors.size() == 0)
	{
		/// Create a default constructor that does nothing.
		getCtorForMethod(nullptr);
	}
	else
	{
		for (auto ctor : ctors)
		{
			getCtorForMethod(ctor);
		}
	}
	
	getModule()->endCopy();
}

void ClassDecl::prebuild()
{
	// Get all the members types so we can specify the body of our type
	std::vector<const Orange::Type *> member_types;
	
	if (getParentClass() != nullptr)
	{
		member_types.push_back(getParentClass()->getType());
	}
	
	for (auto member : getMembers())
	{
		assertExists(member->getType(), "class member lacking type");
		member_types.push_back(member->getType());
	}
	
	if (getType()->isClassTy())
	{
		auto class_ty = getType()->as<Orange::ClassType *>();
		class_ty->specifyMembers(member_types);
	}
	
	// Build the initializer
	getModule()->build(getInitializer());
	
	// Build each pair of ClassMethod/constructor
	auto ctors = getCtors();
	
	if (ctors.size() == 0)
	{
		auto def_ctor = getCtorForMethod(nullptr);
		getModule()->build(def_ctor);
	}
	
	for (unsigned int i = 0; i < ctors.size(); i++)
	{
		if (ctors[i]->isGeneric())
		{
			continue;
		}
		
		getModule()->build(ctors[i]);
		
		auto ctor = getCtorForMethod(ctors[i]);
		getModule()->build(ctor);
	}
	
}

void ClassDecl::build()
{
	if (isGeneric())
	{
		return;
	}
	
	buildStatements();
}

bool ClassDecl::matchesType(const Orange::Type *other) const
{
	if (other->isClassTy() == false)
	{
		return false;
	}
	
	return getType()->matches(other);
}

bool ClassDecl::isAccessible() const
{
	// Classes are always accessible.
	return true;
}

Expression* ClassDecl::access(OString name, const ASTNode *hint) const
{
	assertExists(hint, "ClassDecl::access requires hint");
	
	if (hint->is<const Valued*>() == false)
	{
		if (hasMethod(name))
		{
			return new StaticMethodAccess(this, name);
		}
		else if (hasMember(name) && getMember(name)->getStatic())
		{
			return new NodeReference(getMember(name));
		}
		
		throw fatal_error("Not sure how to handle non-value class access");
	}
	else if (hasMethod(name))
	{
		return new MethodAccess(this, name);
	}
	else if (hasMember(name))
	{
		auto valued = hint->as<const Valued *>();
    	auto memAccess = new MemberAccess(this, (Valued *)valued, name);
    	return memAccess;
	}
	else if (getParentClass())
	{
		return getParentClass()->access(name, hint);
	}
	
	return nullptr;
}

bool ClassDecl::isGeneric() const
{
	return getGenericMembers().size() > 0;
}

Genericable* ClassDecl::createInstance(const Orange::Type *type)
{
	if (isGeneric() == false)
	{
		throw fatal_error("Cannot call createInstance on non-generic class");
	}
	
	getModule()->beginCopy();
	
	auto clone = copy()->as<ClassDecl *>();
	
	getModule()->endCopy();
	
	for (auto& member : clone->getMembers())
	{
		if (member->getType()->isVarTy() &&
			member->getExpression() == nullptr)
		{
			member->setType(new FutureType(getModule()));
		}
	}
	
	/// @todo: this may cause a problem
	auto classTy = Orange::ClassType::get(getModule(), clone);
	clone->setType(classTy);
	
	if (clone->isGeneric())
	{
		throw fatal_error("instance is still a generic!");
	}
	
	clone->m_instance_of = this;
	
	m_instances.push_back(clone);
	
	// Even though whoever is creating the instance of this class will
	// have access to it and its constructor, we don't want it to be
	// searchable outside of its own scope.
	
	// This is so calling a constructor again will refer to the same
	// class, and not the one created here.
	auto anonymous_container = new Block();
	anonymous_container->addStatement(clone);
	findParent<Block *>()->addStatement(anonymous_container, this, 1);
	
	return clone;
}

std::vector<MemberVarDecl*> ClassDecl::getGenericMembers() const
{
	std::vector<MemberVarDecl*> genericMembers;
	for (auto member : getMembers())
	{
		if (member->getType()->isVarTy() &&
			member->getExpression() == nullptr)
		{
			genericMembers.push_back(member);
		}
	}
	
	return genericMembers;
}

Orange::Type* ClassDecl::getRefTy() const
{
	if (isGeneric())
	{
		return Orange::VarType::get(getModule());
	}
	else
	{
		return new ReferenceType(this);
	}
}

bool ClassDecl::hasNamed(OString name, const ASTNode* limit,
						 SearchSettings settings) const
{
	if (Block::hasNamed(name, limit, settings))
	{
		return true;
	}
	
	if (getParentClass() != nullptr)
	{
		return getParentClass()->hasNamed(name, limit, settings);
	}
	
	return false;
}

Named* ClassDecl::getNamed(OString name, const Orange::Type* type,
						   const ASTNode* from, SearchSettings settings) const
{
	auto named = Block::getNamed(name, type, from, settings);
	if (named != nullptr)
	{
		return named;
	}
	
	if (getParentClass() != nullptr)
	{
		return getParentClass()->getNamed(name, type, from, settings);
	}
	
	return nullptr;
}

std::vector<Named *> ClassDecl::getAllNamed(OString name, const ASTNode* from)
const
{
	auto named = Block::getAllNamed(name, from);
	
	if (getParentClass() != nullptr)
	{
		auto parent_named = getParentClass()->getAllNamed(name, from);
		named.insert(named.end(), parent_named.begin(), parent_named.end());
	}
	
	return named;
}

ClassDecl::ClassDecl(OString name, ReferenceType* parentReference)
{
	if (name == "")
	{
		throw fatal_error("name was empty");
	}
	
	// Do nothing
	m_name = name;
	m_parent_ref = parentReference;
	
	addChild(parentReference);
}

ClassDecl::ClassDecl(const ClassDecl& other)
{
	m_name = other.m_name;
	
	if (other.m_parent_class)
	{
    	m_parent_class =
			(ClassDecl *)getModule()->tryGetCopy(other.m_parent_class);
	}
	
	other.defineCopy(this);
	copyStatements(&other);
}