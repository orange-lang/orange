/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"
#include "../OString.h"

class ClassType : public Type
{
private:
	std::vector<const Type *> m_members;
	const OString m_name;
protected:
	ClassType(const OString& name, std::vector<const Type *> members);
public:
	static std::string getSignature(const OString& name,
									const std::vector<const Type *> members);
	
	virtual bool isClassTy() const override;
	virtual bool isAggTy() const override;
	
	virtual std::vector<const Type*> getMemberTys() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual const Type* copyType() const override;
	
	static ClassType* get(Module* mod, const OString& name,
						  std::vector<const Type *> members);
};