/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class DoubleType : public Type
{
protected:
	DoubleType(bool isConst);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isPODTy() const override;
	virtual bool isDoubleTy() const override;
	virtual bool isFloatingPointTy() const override;
	
	virtual BasicType PODTy() const override;
	
	virtual Type* getConst() const override;
	
	static DoubleType* get(Module* mod, bool isConst = false);
};