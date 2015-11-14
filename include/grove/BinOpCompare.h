/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "BinOpExpr.h"

/**
 * BinOpCompare defines any binary operations that deal with comparing values
 * (e.g., <, >, <=, etc.)
 */
class BinOpCompare : public BinOpExpr
{
public:
	virtual void resolve() override;
	virtual void build() override;
	
	BinOpCompare(Expression* LHS, std::string op, Expression* RHS);
};
