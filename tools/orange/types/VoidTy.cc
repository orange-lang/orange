/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/types/VoidTy.h>
#include <orange/generator.h>

VoidTy::VoidTy() {
	m_llvm_ty = Type::getVoidTy(GE::runner()->context());
}

VoidTy* VoidTy::get() {
	if (getDefined("void")) return (VoidTy*)getDefined("void");
	return (VoidTy*)define("void", new VoidTy());
} 
