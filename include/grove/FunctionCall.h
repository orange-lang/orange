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
	OString m_name;
	std::vector<Expression *> m_args;
	
	llvm::Function* getFunction() const;
	FunctionType* getFunctionTy() const;
	
	/// Get the function type we're expecting.
	FunctionType* expectedFunctionTy() const;
	
	Typed* m_node = nullptr;
	
protected:
	void findNode();
public:
	/// Gets the name of the function that we are calling.
	OString getName() const;
	
	/// Gets the arguments in this function call.
	std::vector<Expression *> getArgs() const;
	
	virtual void findDependencies() override;
	
	/// Gets node that we're going to call as a function.
	Typed* getNode() const;
	
	virtual void resolve() override;
	virtual void build() override;
	
	virtual ASTNode* copy() const override;
	
	/// Constructs a new function call.
	/// @param name The name of the function to call.
	/// @param args The argument list of expressions. 
	FunctionCall(OString name, std::vector<Expression *> args);
};