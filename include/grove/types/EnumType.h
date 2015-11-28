/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

class EnumType : public Type
{
private:
	Type* m_contained = nullptr;
protected:
	EnumType(Type* contained, bool isConst);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual Type* getBaseTy() const override;
	
	virtual Type* getRootTy() const override;
	
	virtual Type* getConst() const override;
	
	static EnumType* get(Type* contained, bool isConst = false);
};