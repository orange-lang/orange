/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_POINTER_TY_H__
#define __ORANGE_POINTER_TY_H__

#include "OrangeTy.h"

using namespace llvm;

class PointerTy : public OrangeTy {
private:
	OrangeTy* m_pointer = nullptr;

	PointerTy(OrangeTy* pointerElement);
public:
	virtual std::string string() const; 

	virtual bool isPointerTy() const { return true; }

	virtual OrangeTy* getBaseType() { return m_pointer->getBaseType(); }
	/** 
	 * Gets whether or not the underlying type is 
	 * signed or not. 
	 */
	virtual bool isSigned() const; 

	virtual OrangeTy* getPointerElementType() { return m_pointer; }

	static PointerTy* get(OrangeTy* pointerElement);
}; 

#endif 