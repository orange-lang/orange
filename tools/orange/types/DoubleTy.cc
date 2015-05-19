/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/DoubleTy.h>
#include <orange/generator.h>

DoubleTy::DoubleTy() {
	m_llvm_ty = Type::getDoubleTy(GE::runner()->context());
}

DoubleTy* DoubleTy::get() {
	if (getDefined("double")) return (DoubleTy*)getDefined("double");
	return (DoubleTy*)define("double", new DoubleTy());
}
