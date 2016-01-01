/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

namespace Orange { class EnumType; }

class Orange::EnumType : public Orange::Type
{
private:
	const Type* m_contained = nullptr;
protected:
	EnumType(const Type* contained, bool isConst);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual const Type* getBaseTy() const override;
	
	virtual const Type* getRootTy() const override;
	
	virtual const Type* getConst() const override;
	
	virtual const Type* copyType() const override;
	
	static EnumType* get(Module* mod, const Type* contained, bool isConst = false);
};