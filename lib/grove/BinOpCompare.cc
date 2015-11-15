/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpCompare.h>
#include <grove/types/BoolType.h>
#include <util/assertions.h>

void BinOpCompare::resolve()
{
	BinOpExpr::resolve();
	setType(BoolType::get());
}

void BinOpCompare::build()
{
	getLHS()->build();
	getRHS()->build();
	
	auto vLHS = getLHS()->getValue();
	auto vRHS = getLHS()->getValue();
	
	assertExists(vLHS, "LHS did not generate a value.");
	assertExists(vRHS, "RHS did not generate a value.");
	
	if (requiresCast())
	{
		auto prec = compare(getLHS(), getRHS());
		
		switch (prec)
		{
			case LOWER_PRECEDENCE:
				vLHS = getLHS()->castTo(getRHS());
				break;
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
	
	// Get the operation to use.
	throw std::runtime_error("BinOpCompare::build NYI");
}

BinOpCompare::BinOpCompare(Expression* LHS, std::string op, Expression* RHS)
:BinOpExpr(LHS, op, RHS)
{
	// Do nothing.
}