#include "gen/ArgExpr.h"
#include "gen/generator.h"

Statement* ArgExpr::clone() {
	AnyType *clonedType = type ? type->clone() : nullptr; 
	ArgExpr *ret = new ArgExpr(clonedType, nullptr); 
	ret->name = name;
	return ret; 
}

Type* ArgExpr::getType() {
	if (type == nullptr) return nullptr; 
	return type->getType();
}

ArgExpr::ArgExpr(AnyType* type, std::string* name) {
	this->type = type;

	if (type != nullptr) {
		this->isLocked = true;
	}

	this->name = name ? *name : "";
}

