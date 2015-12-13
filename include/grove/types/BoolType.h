/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "UIntType.h"

class BoolType : public UIntType
{
protected:
	BoolType(bool isConst);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual Type* getConst() const override;
	
	virtual bool isBoolTy() const override;
	virtual bool isIntTy() const override;
	
	static BoolType* get(Module* mod, bool isConst = false);
};