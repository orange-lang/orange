/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Expression.h"

/**
 * BinOpExpr is the base class for any grammar defined as expr operator expr.
 */
class BinOpExpr : public Expression {
private:
	Expression* m_LHS;
	Expression* m_RHS;
	
	std::string m_operator;
protected:
	bool areTypesCompatible() const;
	bool areTypesCastable() const;
	bool requiresCast() const;
	
	bool isFloatingPointOperation() const;
	bool areOperandsSigned() const;
public:
	Expression* getLHS() const;
	Expression* getRHS() const;
	
	std::string getOperator() const;
	
	virtual void resolve() override;
	
	BinOpExpr(Expression* LHS, std::string op, Expression* RHS);
};
