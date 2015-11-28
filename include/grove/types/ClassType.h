/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

class ClassType : public Type
{
private:
	std::vector<Type *> m_members;
protected:
	ClassType(std::vector<Type *> members);
public:
	static std::string getSignature(std::vector<Type *> members);
	
	virtual bool isClassTy() const override;
	
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	static ClassType* get(std::vector<Type *> members);
};