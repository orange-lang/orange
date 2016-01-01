/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/exceptions/binop_error.h>
#include <grove/exceptions/fatal_error.h>

#include <grove/types/Type.h>

binop_error::binop_error(CodeBase* element, const Orange::Type* LHS, OString op,
						 const Orange::Type* RHS)
: code_error(element)
{
	if (LHS == nullptr)
	{
		throw fatal_error("LHS is nullptr");
	}
	
	if (RHS == nullptr)
	{
		throw fatal_error("RHS is nullptr");
	}
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: "
	   << "operator " << op.str() << " cannot be used with operands of "
	   << "types " << LHS->getString() << " and " << RHS->getString() << "\n"
	   << getContext(element);
	
	m_error = ss.str();
}

binop_error::binop_error(CodeBase* element, const Orange::Type* LHS, OString op,
						 const Orange::Type* RHS, const Orange::Type* expectLHS,
						 const Orange::Type* expectRHS)
: code_error(element)
{
	if (LHS == nullptr)
	{
		throw fatal_error("LHS is nullptr");
	}
	
	if (RHS == nullptr)
	{
		throw fatal_error("RHS is nullptr");
	}
	
	if (expectLHS == nullptr)
	{
		throw fatal_error("expectLHS is nullptr");
	}
	
	if (expectRHS == nullptr)
	{
		throw fatal_error("expectRHS is nullptr");
	}
	
	
	std::stringstream ss;
	
	ss << fileWithPosition(element) << ": error: "
	   << "operator " << op.str() << " cannot be used with operands of "
	   << "types " << LHS->getString() << " and " << RHS->getString() << " "
	   << "(expected " << expectLHS->getString() << " and "
	   << expectRHS->getString() << ")\n"
	   << getContext(element);
	
	m_error = ss.str();
}

