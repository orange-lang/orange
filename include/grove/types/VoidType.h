/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

namespace Orange { class VoidType; }

class Orange::VoidType : public Orange::Type
{
protected:
	VoidType();
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isPODTy() const override;
	virtual bool isVoidTy() const override;
	
	virtual BasicType PODTy() const override;
	
	static VoidType* get(Module* mod);
};