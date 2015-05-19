/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/FloatTy.h>
#include <orange/generator.h>

FloatTy::FloatTy() {
	m_llvm_ty = Type::getFloatTy(GE::runner()->context());
}

FloatTy* FloatTy::get() {
	if (getDefined("float")) return (FloatTy*)getDefined("float");
	return (FloatTy*)define("float", new FloatTy());
}
