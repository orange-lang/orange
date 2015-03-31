/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/Reference.h"
#include "gen/generator.h"

std::string Reference::string() {
	std::stringstream ss;
	ss << "&" << value->string();
	return ss.str();
}

Type* Reference::getType() {
	Type *vType = value->getType();
	if (vType->isArrayTy()) {
		return vType->getArrayElementType()->getPointerTo();
	}

	return value->getType()->getPointerTo();
}

void Reference::resolve() {
	if (resolved)
		return;
	resolved = true; 

	value->resolve();
}

Value* Reference::Codegen() {
	Value *v = value->Codegen();
	return v;
}
