/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/IDTy.h>

IDTy* IDTy::get() {
	if (getDefined("id")) return (IDTy*)getDefined("id");
	return (IDTy*)define("id", new IDTy());
} 
