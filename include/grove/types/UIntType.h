/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class UIntType : public Type
{
private:
	unsigned int m_width = 0;
	
	UIntType(unsigned int width);
public:
	virtual std::string getSignature() const;
	
	virtual bool isPODTy() const;
	virtual bool isSigned() const;
	virtual bool isIntTy() const;
	
	virtual BasicType PODTy() const;
	
	static UIntType* get(unsigned int width);
};