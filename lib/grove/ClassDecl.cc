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
#include <grove/MethodAccess.h>
#include <grove/Constructor.h>
#include <grove/ExpressionCall.h>
#include <grove/AccessExpr.h>
#include <grove/BinOpAssign.h>

#include <grove/types/VoidType.h>

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

void ClassDecl::createCtor(ClassMethod *method) const
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
		auto this_ty = new ReferenceType(this);
		params.push_back(new Parameter(this_ty->getPointerTo(), "this"));
	}
	
	auto func = new Constructor(this, getName(), params);
	
	// The functions return type is this class' type.
	func->setReturnType(VoidType::get(getModule()));
	
	// The class constructor needs to instantiate all of its variables that have
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
		
		func->addStatement(assign);
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
	findParent<Block *>()->addStatement(func, this, 1);
	
	// Request a resolve of our function.
	getModule()->findDependencies(func);
	getModule()->resolve(func);
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

void ClassDecl::findDependencies()
{
	for (auto& member : getMembers())
	{
		addDependency(member);
	}
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
	std::vector<const Type *> member_types;
	
	for (auto member : getMembers())
	{
		assertExists(member->getType(), "class member lacking type");
		member_types.push_back(member->getType());
	}
	
	// Set our type to an explicit reference type to this class.
	auto classTy = ClassType::get(getModule(), m_name, member_types);
	setType(new ReferenceType(this, classTy));
	
	// Create all of our constructors.
	getModule()->beginCopy();
	
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
	
	getModule()->endCopy();
}

void ClassDecl::build()
{
	buildStatements();
}

bool ClassDecl::matchesType(const Type *other) const
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
	if (hint->is<const Valued *>() == false)
	{
		throw fatal_error("ClassDecl::access requires Valued hint");
	}
	
	if (hasMethod(name))
	{
		return new MethodAccess(this, name);
	}
	
	if (hasMember(name))
	{
		auto valued = hint->as<const Valued *>();
    	auto memAccess = new MemberAccess(this, (Valued *)valued, name);
    	return memAccess;
	}
	
	return nullptr;
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

ClassDecl::ClassDecl(const ClassDecl& other)
{
	copyStatements(&other);
	other.defineCopy(this);
}