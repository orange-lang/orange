/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/SuperCall.h>
#include <grove/ClassDecl.h>
#include <grove/ClassMethod.h>
#include <grove/IDReference.h>

#include <grove/types/FunctionType.h>
#include <grove/types/VarType.h>
#include <grove/types/PointerType.h>

#include <grove/exceptions/code_error.h>

#include <util/copy.h>
#include <util/assertions.h>

ASTNode* SuperCall::copy() const
{
	return new SuperCall(*this);
}

std::vector<ObjectBase**> SuperCall::getMemberNodes()
{
	auto list = ExpressionCall::getMemberNodes();
	list.insert(list.end(), {
		(ObjectBase **)&m_this_param
	});
	return list;
}

std::vector<std::vector<ObjectBase *>*> SuperCall::getMemberLists()
{
	return ExpressionCall::getMemberLists();
}

Orange::FunctionType* SuperCall::expectedFunctionTy() const
{
	auto ty_list = std::vector<const Orange::Type *>();
	for (auto arg : m_args)
	{
		assertExists(arg->getType(), "Arg doesn't have assigned type");
		
		if (arg == m_this_param)
		{
			ty_list.push_back(Orange::VarType::get(getModule()));
			continue;
		}
		
		// Cast arrays to pointers so we can pass-by-reference
		if (arg->getType()->isArrayTy())
		{
			ty_list.push_back(Orange::PointerType::get(getModule(),
													   arg->getType()->getBaseTy()));
			continue;
		}
		
		ty_list.push_back(arg->getType());
	}
	
	// Put a wildcard on the return type.
	return Orange::FunctionType::get(getModule(),
									 Orange::VarType::get(getModule()),
									 ty_list);
}

void SuperCall::initialize()
{
	m_class = findParent<ClassDecl *>();
	
	if (m_class == nullptr)
	{
		throw code_error(this, []() -> std::string
						 {
							 return "Calling a super constructor can only be "
							 "used from a class";
						 });
	}
}

void SuperCall::findDependencies()
{
	ASTNode::findDependencies();
	
	auto named = m_class->getParentClass()->getCtors();
	for (auto n : named)
	{
		addDependency(n);
	}
}

void SuperCall::findNode()
{
	auto parent_class = m_class->getParentClass();
	
	SearchSettings settings;
	settings.includeLimit = false;
	settings.createGeneric = true;
	settings.searchWholeTree = false;
	settings.filter = [this](Named* named) -> bool
	{
		return named->is<ClassMethod *>() &&
			named->as<ClassMethod *>()->isConstructor();
	};
	
	
	auto def = parent_class->getNamed(parent_class->getName(),
									  expectedFunctionTy(), nullptr, settings);
	if (def == nullptr)
	{
		throw code_error(this, parent_class, [] () -> std::string
						 {
							return "Parent class has no matching constructor";
						 });
	}
	
	// Determine type
	setExpr(def->as<ASTNode *>());
}

void SuperCall::resolve()
{
	if (m_class->getParentClass() == nullptr)
	{
		throw code_error(this, m_class, [] () -> std::string
						 {
							 return "Class does not have a parent";
						 });
	}
	
	auto parent_method = findParent<ClassMethod *>();
	if (parent_method->isConstructor() == false)
	{
		throw code_error(this, parent_method, [] () -> std::string
						 {
							 return "Can only call a parent constructor from "
							 "a constructor";
						 });
	}
	
	if (getExpr() == nullptr)
	{
		findNode();
	}
	
	ExpressionCall::resolve();
}

SuperCall::SuperCall(std::vector<Expression *> args)
: ExpressionCall(args)
{
	m_this_param = new IDReference("this");
	
	if (args.size() == 0)
	{
		addChild(m_this_param);
	}
	else
	{
		addChild(m_this_param, m_args.at(0), 0);
	}
	
	m_args.insert(m_args.begin(), m_this_param);
}

SuperCall::SuperCall(const SuperCall& other)
: ExpressionCall(copyVector(other.getArgs()))
{
	other.defineCopy(this);
}