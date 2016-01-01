/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

namespace Orange { class UIntType; }

class Orange::UIntType : public Orange::Type
{
private:
	unsigned int m_width = 0;

protected:
	UIntType(unsigned int width, bool isConst);
	
public:
	static std::string getSignature(unsigned int width, bool isConst);
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isPODTy() const override;
	virtual bool isSigned() const override;
	virtual bool isIntTy() const override;
	
	virtual unsigned int getIntegerBitWidth() const override;
	
	virtual BasicType PODTy() const override;
	
	virtual Type* getConst() const override;
	
	static UIntType* get(Module* mod, unsigned int width, bool isConst = false);
};