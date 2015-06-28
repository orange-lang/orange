/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_VAR_TY_H__
#define __ORANGE_VAR_TY_H__

#include "OrangeTy.h"

using namespace llvm;

class VarTy : public OrangeTy {
public:
	virtual std::string string() const { return "var"; }

	virtual bool isVarTy() const { return true; }

	static VarTy* get(); 
}; 

#endif 