/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include "gen/ArgExpr.h"
#include "gen/generator.h"

Type* ArgExpr::getType() {
	if (type == nullptr) return nullptr; 
	return type->getType();
}

AnyType* ArgExpr::getAnyType() const { 
	return type; 
}

void ArgExpr::setType(AnyType *newType) { 
	type = newType; 
}

Statement* ArgExpr::clone() {
	// Only clone the type if it exists.
	AnyType *clonedType = type ? type->clone() : nullptr; 
	ArgExpr *ret = new ArgExpr(clonedType, nullptr); 
	ret->name = name;
	return ret; 
}

std::string ArgExpr::getName() const {
 return name; 
} 

bool ArgExpr::isSigned() { 
	return type->isSigned(); 
}


std::string ArgExpr::string() {
	std::stringstream ss;
	// If the type exists, add it to the result.
	if (type && type->getTypeStr() != "") {
		ss << type->getTypeStr() << " ";
	}
	ss << name;
	return ss.str();
}

ArgExpr::ArgExpr(AnyType* type, std::string* name) {
	this->type = type;

	// If the the type exists, lock down this variable. 
	if (type != nullptr) {
		this->isLocked = true;
	}

	this->name = name ? *name : "";
}

