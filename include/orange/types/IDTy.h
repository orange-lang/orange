/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ID_TY_H__
#define __ORANGE_ID_TY_H__

#include "OrangeTy.h"

using namespace llvm;

class IDTy : public OrangeTy {
public:
	virtual std::string string() const { return "id"; }

	virtual bool isIDTy() const { return true; }

	static IDTy* get(); 
}; 

#endif 