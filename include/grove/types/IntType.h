/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class IntType : public Type
{
private:
	unsigned int m_width = 0;

protected:
	IntType(unsigned int width);
	
public:
	virtual std::string getSignature() const override;
	
	virtual bool isPODTy() const override;
	virtual bool isSigned() const override;
	virtual bool isIntTy() const override;
	
	virtual unsigned int getIntegerBitWidth() const override;
	
	unsigned int getWidth() const;
	
	virtual BasicType PODTy() const override;
	
	static IntType* get(unsigned int width);
};