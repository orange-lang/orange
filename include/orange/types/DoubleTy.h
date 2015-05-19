/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_DOUBLE_TY_H__
#define __ORANGE_DOUBLE_TY_H__

#include "OrangeTy.h"

class DoubleTy : public OrangeTy {
private:
	DoubleTy();
public:
	virtual std::string string() const { return "double"; }
	virtual std::string typeSuffix() const { return "d"; } 

	virtual bool isDoubleTy() const { return true; }
	virtual bool isFloatingPointTy() const { return true; }

	static DoubleTy* get();
}; 

#endif 