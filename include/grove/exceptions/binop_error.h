/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "code_error.h"
#include "../OString.h"

namespace Orange { class Type; }

/**
 * binop_error is used for errors of a binary operation between two 
 * incompatible types.
 */
class binop_error : public code_error
{
public:
	binop_error(CodeBase* element, const Orange::Type* LHS, OString op,
				const Orange::Type* RHS);
	
	binop_error(CodeBase* element, const Orange::Type* LHS, OString op,
				const Orange::Type* RHS, const Orange::Type* expectLHS,
				const Orange::Type* expectRHS);
};