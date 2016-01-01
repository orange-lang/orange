/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "ExpressionCall.h"

class FunctionCall : public ExpressionCall {
private:
	OString m_name;
protected:
	virtual void findNode();
public:
	/// Gets the name of the function that we are calling.
	OString getName() const;
	
	virtual void findDependencies() override;
	
	virtual void resolve() override;
	
	virtual ASTNode* copy() const override;
	
	/// Constructs a new function call.
	/// @param name The name of the function to call.
	/// @param args The argument list of expressions. 
	FunctionCall(OString name, std::vector<Expression *> args);
	FunctionCall(const FunctionCall& other);
};