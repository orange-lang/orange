/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_VARIADIC_ARRAY_TY_H__
#define __ORANGE_VARIADIC_ARRAY_TY_H__

#include "OrangeTy.h"

using namespace llvm;

class VariadicArrayTy : public OrangeTy {
private:
	OrangeTy* m_internal_ty = nullptr;
	Expression *m_count = nullptr;

	VariadicArrayTy(OrangeTy* internalTy, Expression* count);
public:
	virtual std::string string() const; 

	virtual bool isArrayTy() const { return true; }

	virtual bool isVariadicArray() const { return true; }

	virtual bool isSigned() const; 

	virtual OrangeTy* getArrayElementType() { return m_internal_ty; }

	virtual Expression* getVariadicArrayElement() { return m_count; }

	virtual OrangeTy* getBaseType() { return m_internal_ty->getBaseType(); }

	static VariadicArrayTy* get(OrangeTy* internalTy, Expression* count);
}; 

#endif 