/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "FunctionCall.h"

class CtorCall : public FunctionCall
{
public:
	virtual bool hasPointer() const override;
	virtual llvm::Value* getPointer() const override;
	virtual llvm::Value* getValue() const override;
	
	virtual void resolve() override;
	virtual void build() override;
	
	CtorCall(OString name, std::vector<Expression *> args);
};