/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_FLOAT_TY_H__
#define __ORANGE_FLOAT_TY_H__

#include "OrangeTy.h"

class FloatTy : public OrangeTy {
private:
	FloatTy();
public:
	virtual std::string string() const { return "float"; }
	virtual std::string typeSuffix() const { return "f"; } 

	virtual bool isFloatTy() const { return true; }
	virtual bool isFloatingPointTy() const { return true; }

	static FloatTy* get();
}; 

#endif 