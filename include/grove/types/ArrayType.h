/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class Expression;

class ArrayType : public Type
{
private:
	Type* m_contained = nullptr;
	unsigned int m_size = 0;
	
protected:
	ArrayType(Type* contained, unsigned int size, bool isConst);
	
public:
	virtual std::string getString() const override;
	
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual bool isArrayTy() const override;
	
	virtual Type* getBaseTy() const override;
	
	virtual Type* getRootTy() const override;
	
	virtual Type* getConst() const override;
	
	static ArrayType* get(Module* mod, Type* contained, unsigned int size,
						  bool isConst = false);
};