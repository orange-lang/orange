/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class VarType : public Type
{
protected:
	VarType(bool isConst);
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isVarTy() const override;
	
	virtual Type* getConst() const override;
	
	static VarType* get(bool isConst = false);
};