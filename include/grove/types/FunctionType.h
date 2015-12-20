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
	const Type* m_ret_type = nullptr;
	bool m_var_arg = false;
	
	std::vector<const Type*> m_args;
	
	static std::string getSignature(const Type* retType,
									std::vector<const Type*> args,
									bool vaarg);
protected:
	FunctionType(const Type* retType, std::vector<const Type*> args, bool vaarg);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual bool isFunctionTy() const override;
	
	virtual const Type* getBaseTy() const override;
	
	virtual const Type* getRootTy() const override;
	
	virtual const Type* getReturnTy() const;
	
	std::vector<const Type *> getArgs() const;
	
	bool isVarArg() const;
	
	static FunctionType* get(Module* mod, const Type* retType,
							 std::vector<const Type*> args,
							 bool vaarg = false);
};