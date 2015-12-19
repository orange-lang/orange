/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CtorCall.h>
#include <grove/Constructor.h>
#include <grove/ClassDecl.h>
#include <grove/Module.h>

#include <grove/types/Type.h>
#include <grove/types/ReferenceType.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

bool CtorCall::hasPointer() const
{
	return true;
}

llvm::Value* CtorCall::getPointer() const
{
	return m_value;
}

llvm::Value* CtorCall::getValue() const
{
	return IRBuilder()->CreateLoad(m_value);
}

bool CtorCall::transferrable() const
{
	return true;
}

ClassDecl* CtorCall::findClass() const
{
	SearchSettings settings;
	settings.createGeneric = false;
	settings.forceTypeMatch = false;
	settings.includeLimit = true;
	settings.searchWholeTree = true;
	
	settings.filter = [](Named* named)
	{
		return named->is<TypeProvider *>();
	};
	
	return findNamed(getName(), nullptr, settings)->as<ClassDecl *>();
}

void CtorCall::resolve()
{
	auto the_class = findClass();
	auto class_ty = the_class->getType();
	assertExists(class_ty, "Class has no defined type");
	
	m_this_param->setType(class_ty->getPointerTo());
	
	FunctionCall::resolve();
	
	if (getExpr()->is<Constructor *>() == false)
	{
		throw fatal_error("CtorCall not looking at a Constructor!");
	}

	auto refType = new ReferenceType(the_class);
	addChild(refType);
	
	getModule()->resolve(refType);

	setType(refType);
}

void CtorCall::build()
{
	auto val = IRBuilder()->CreateAlloca(getType()->getLLVMType());
	m_this_param->setValue(val);
	
	FunctionCall::build();
	
	setValue(val);
}

CtorCall::CtorCall(OString name, std::vector<Expression *> args)
: FunctionCall(name, args)
{
	m_this_param = new Expression();
	
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