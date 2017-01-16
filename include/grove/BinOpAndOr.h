/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "BinOpExpr.h"

class BinOpAndOr : public BinOpExpr
{
public:
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	BinOpAndOr(Expression* LHS, OString op, Expression* RHS);
};