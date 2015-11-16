/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpAssign.h>
#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/IRBuilder.h>

void BinOpAssign::resolve()
{
	BinOpExpr::resolve();
	
	if (getLHS()->hasPointer() == false)
	{
		throw std::invalid_argument("LHS doesn't refer to a memory address");
	}
	
	assertExists(getLHS()->getType(), "LHS doesn't have a type");
	setType(getLHS()->getType());
}

void BinOpAssign::build()
{
	getLHS()->build();
	getRHS()->build();
	
	auto vLHS = getLHS()->getValue();
	auto vRHS = getRHS()->getValue();
	
	assertExists(vLHS, "LHS did not generate a value.");
	assertExists(vRHS, "RHS did not generate a value.");
	
	// Cast RHS to LHS if LHS != RHS
	if (requiresCast())
	{
		auto prec = compare(getLHS(), getRHS());
		
		switch (prec)
		{
			case LOWER_PRECEDENCE:
			case HIGHER_PRECEDENCE:
				vRHS = getRHS()->castTo(getLHS());
				break;
			case INCOMPATIBLE:
				throw std::runtime_error("Cannot cast types.");
				break;
			default:
				// Do nothing
				break;
		}
	}
	
	assertEqual(vLHS, vRHS, "LHS and RHS do not have the same type!");
	
	auto ptr = getLHS()->getPointer();
	assertExists(ptr, "LHS didn't give a pointer");
	
	assertEqual<VAL, PTR>(vRHS, ptr, "Can't assign RHS to address");
	IRBuilder()->CreateStore(vRHS, ptr);
	
	setValue(vRHS);
}

BinOpAssign::BinOpAssign(Expression* LHS, std::string op, Expression* RHS)
:BinOpExpr(LHS, op, RHS)
{
	if (op != "=")
	{
		throw std::invalid_argument("Unknown assign operator");
	}
}