/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Expression.h"

namespace llvm { class Function; }

class FunctionType;

class FunctionCall : public Expression {
private:
	std::string m_name;
	std::vector<Expression *> m_args;
	
	llvm::Function* getFunction() const;
	FunctionType* getFunctionTy() const;
public:
	/// Gets the name of the function that we are calling.
	std::string getName() const;
	
	/// Gets the arguments in this function call.
	std::vector<Expression *> getArgs() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	/// Constructs a new function call.
	/// @param name The name of the function to call.
	/// @param args The argument list of expressions. 
	FunctionCall(std::string name, std::vector<Expression *> args);
};