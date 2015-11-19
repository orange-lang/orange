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
	bool m_var_arg = false;
	
	std::vector<Type*> m_args;
	
	static std::string getSignature(Type* retType, std::vector<Type*> args,
									bool vaarg);
protected:
	FunctionType(Type* retType, std::vector<Type*> args, bool vaarg);
public:
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual bool isFunctionTy() const override;
	
	virtual Type* getBaseTy() const override;
	
	virtual Type* getRootTy() const override;
	
	virtual Type* getReturnTy() const;
	
	std::vector<Type *> getArgs() const;
	
	bool isVarArg() const;
	
	static FunctionType* get(Type* retType, std::vector<Type*> args,
							 bool vaarg = false);
};