/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/LoopTerminator.h>
#include <grove/Loop.h>

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>

OString LoopTerminator::getTerminatorStr() const
{
	return m_terminator;
}

ASTNode* LoopTerminator::copy() const
{
	return new LoopTerminator(m_terminator);
}

bool LoopTerminator::isTerminator() const
{
	return true;
}

void LoopTerminator::resolve()
{
	auto parent_loop = findParent<Loop *>();
	assertExists(parent_loop, "Not in a loop");
}

void LoopTerminator::build()
{
	auto parent_loop = findParent<Loop *>();
	
	if (getTerminatorStr() == "break")
	{
		IRBuilder()->CreateBr(parent_loop->getContinueBlock());
	}
	else if (parent_loop->getAfterthought() != nullptr)
	{
		IRBuilder()->CreateBr(parent_loop->getAfterthoughtBlock());
	}
	else if (parent_loop->getConditionBlock() != nullptr)
	{
		IRBuilder()->CreateBr(parent_loop->getConditionBlock());
	}
	else
	{
		IRBuilder()->CreateBr(parent_loop->getBodyBlock());
	}
}

LoopTerminator::LoopTerminator(OString terminator)
{
	if (terminator != "break" && terminator != "continue" &&
		terminator != "loop")
	{
		throw fatal_error("unkown terminator passed to LoopTerminator");
	}
	
	m_terminator = terminator;
}