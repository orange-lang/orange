/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ARRAY_TY_H__
#define __ORANGE_ARRAY_TY_H__

#include "OrangeTy.h"

using namespace llvm;

class ArrayTy : public OrangeTy {
private:
	OrangeTy* m_internal_ty = nullptr;
	unsigned int m_count = 0; 

	ArrayTy(OrangeTy* internalTy, unsigned int count);
public:
	virtual std::string string() const; 

	virtual bool isArrayTy() const { return true; }

	virtual bool isConstantArray() const { return true; }

	virtual bool isVariadicArray() const { return m_internal_ty->isVariadicArray(); }

	virtual bool isSigned() const; 

	virtual OrangeTy* getArrayElementType() { return m_internal_ty; }

	virtual unsigned int getArrayElements() { return m_count; }

	virtual OrangeTy* getBaseType() { return m_internal_ty->getBaseType(); }

	static ArrayTy* get(OrangeTy* internalTy, unsigned int count);
}; 

#endif 