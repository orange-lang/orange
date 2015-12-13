/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/CtorCall.h>
#include <grove/Constructor.h>

#include <grove/types/Type.h>

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

void CtorCall::resolve()
{
	findNode();
	
	// For now, this doesn't need to be any different:
	// the value of the constructor will be copied
	FunctionCall::resolve();
	
	if (getNode()->is<Constructor *>() == false)
	{
		throw fatal_error("CtorCall not looking at a Constructor!");
	}
}

void CtorCall::build()
{
	auto val = IRBuilder()->CreateAlloca(getType()->getLLVMType());
	
	FunctionCall::build();
	
	IRBuilder()->CreateStore(FunctionCall::getValue(), val);
	setValue(val);
}

CtorCall::CtorCall(OString name, std::vector<Expression *> args)
: FunctionCall(name, args)
{
	// Do nothing.
}