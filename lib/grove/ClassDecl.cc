/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
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
#include <grove/Constructor.h>

#include <grove/exceptions/code_error.h>
#include <grove/exceptions/already_defined_error.h>

#include <grove/types/ClassType.h>
#include <grove/types/ReferenceType.h>

#include <util/assertions.h>
#include <util/copy.h>

ASTNode* ClassDecl::copy() const
{
	auto class_copy = new ClassDecl(getName());
	class_copy->copyStatements(this);
	return class_copy;
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
		if (child->is<ClassMethod *>())
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

void ClassDecl::createCtor(ClassMethod *method) const
{
	assertExists(getParent(), "class has no parent!");
	
	std::vector<Parameter *> params;
	
	if (method != nullptr)
	{
		params = copyVector(method->getBasicParams());
	}
	
	auto func = new Constructor(this, getName(), params);
	
	// The functions return type is this class' type.
	auto refType = new ReferenceType(this);
	func->addChild(refType);
	func->addDependency(refType);
	func->setReturnType(refType);
	
	// The class constructor needs to create an instance of its return
	// type, then instantiate all of its variables that have values,
	// and finally call the method, if one exists.
	
	// Create the instance
	auto class_instance = new VarDecl(getType(), "instance", nullptr);
	
	/// @todo: Instantiate members with default values
	/// @todo: Call the method if one exists.
	
	auto load_instance = new IDReference("instance");
	auto ret_stmt = new ReturnStmt(load_instance);
	
	// Add all the statements to the class.
	func->addStatement(class_instance);
	func->addStatement(ret_stmt);
	
	// Add the function to our parent block after this class.
	// There's never a reason to add it to our parent as well, since
	// our parent will always be the parent block.
	findParent<Block *>()->addStatement(func, this, 1);
	
	// Request a resolve of our function.
	getModule()->findDependencies(func);
	getModule()->resolve(func);
}

MemberVarDecl* ClassDecl::getMember(OString &name) const
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

void ClassDecl::resolve()
{
	// Make sure that the class's name is unique.
	SearchSettings settings;
	settings.createGeneric = false;
	settings.includeLimit = false;
	
	auto named = findNamed(getName(), nullptr, settings);
	if (named != nullptr && named != this)
	{
		auto base = named->as<CodeBase *>();
		throw already_defined_error(&m_name, base, m_name, false);
	}
	
	// First, make sure that all of the children are ClassTopLevels.
	for (auto child : getChildren())
	{
		if (child->is<ClassTopLevel *>() == false)
		{
			throw code_error(child, []() -> std::string
				{
					return "invalid child of class";
				});
		}
	}
	
	// Get all the members types
	std::vector<Type *> member_types;
	
	for (auto member : getMembers())
	{
		assertExists(member->getType(), "class member lacking type");
		member_types.push_back(member->getType());
	}
	
	setType(ClassType::get(getModule(), member_types));
	
	// Create all of our constructors.
	auto ctors = getCtors();
	if (ctors.size() == 0)
	{
		/// Create a default constructor that does nothing.
		createCtor(nullptr);
	}
	else
	{
		for (auto ctor : ctors)
		{
			createCtor(ctor);
		}
	}
}

void ClassDecl::build()
{
	buildStatements();
}

bool ClassDecl::matchesType(Type *other) const
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
	if (((ASTNode *)hint)->is<Valued *>() == false)
	{
		throw fatal_error("ClassDecl::access requires Valued hint");
	}
	
	auto valued = ((ASTNode *)hint)->as<Valued *>();
	auto memAccess = new MemberAccess(this, valued, name);
	
	getModule()->findDependencies(memAccess);
	getModule()->resolve(memAccess);
	getModule()->addChild(memAccess);
	
	return memAccess;
}

ClassDecl::ClassDecl(OString name)
{
	if (name == "")
	{
		throw fatal_error("name was empty");
	}
	
	// Do nothing
	m_name = name;
}