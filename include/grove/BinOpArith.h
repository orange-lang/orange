/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "BinOpExpr.h"

/**
 * BinOpArith defines any binary operations that deal with arithmetic 
 * (e.g., +, -, *, /, %, etc)
 */
class BinOpArith : public BinOpExpr
{
public:
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	BinOpArith(Expression* LHS, OString op, Expression* RHS);
	BinOpArith(const BinOpArith& other);
};