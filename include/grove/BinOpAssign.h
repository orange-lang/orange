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
 * BinOpAssign defines any binary operations that deal with assigning
 * a value to a variable.
 */
class BinOpAssign : public BinOpExpr
{
public:
	virtual void resolve() override;
	virtual void build() override;
	
	/// Determines whether or not the operator also
	/// does some form of artithmetic.
	bool doesArithmetic() const;
	
	/// If the operator does arithmetic, get the
	/// arithmetic operator.
	OString getArithOp() const;

	virtual ASTNode* copy() const override;
	
	BinOpAssign(Expression* LHS, OString op, Expression* RHS);
};
