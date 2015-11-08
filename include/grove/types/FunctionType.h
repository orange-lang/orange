/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class FunctionType : public Type
{
private:
	Type* m_ret_type = nullptr;
	
	std::vector<Type*> m_args;
	
	static std::string getSignature(Type* retType, std::vector<Type*> args);
	
	FunctionType(Type* retType, std::vector<Type*> args);
public:
	virtual std::string getSignature() const;
	
	virtual bool isSigned() const;
	
	virtual bool isFunctionTy() const;
	
	Type* getBaseTy();
	
	Type* getRootTy();
	
	Type* getReturnTy() const;
	
	std::vector<Type *> getArgs() const;
	
	static FunctionType* get(Type* retType, std::vector<Type*> args);
};