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

#include <grove/types/FunctionType.h>

#include <grove/exceptions/code_error.h>

#include <util/copy.h>

ASTNode* SuperCall::copy() const
{
	return new SuperCall(*this);
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
	
	auto def = parent_class->findNamed(parent_class->getName(),
									   expectedFunctionTy(), settings);
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
	// Do nothing.
}

SuperCall::SuperCall(const SuperCall& other)
: ExpressionCall(copyVector(other.getArgs()))
{
	other.defineCopy(this);
}