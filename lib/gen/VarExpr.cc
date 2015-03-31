/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/VarExpr.h"
#include "gen/generator.h"

Type *VarExpr::getType() {
	Symobj *o = CG::Symtabs.top()->find(name);
	if (o == nullptr || o->getType() == nullptr) { 
		return nullptr;
	}

	if (o->getType()->isPointerTy() == false) {
		std::cerr << "BUG: variable not registered as a pointer. report this bug.\n";
		exit(1);
	}

	return o->getType()->getPointerElementType();
}

bool VarExpr::isSigned() {
	Symobj *o = CG::Symtabs.top()->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		exit(1);
	}	

	return o->isSigned;
}

Value* VarExpr::Codegen() {
	Symobj *o = CG::Symtabs.top()->find(name);
	if (o == nullptr) {
		std::cerr << "Fatal: no symbol " << name << " found.\n";
		return nullptr;
	}

	return o->getValue();
}