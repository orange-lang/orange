#include "gen/ArgExpr.h"
#include "gen/generator.h"

ArgExpr::ArgExpr(AnyType* type, std::string* name) {
	this->type = type;

	if (type != nullptr) {
		this->isLocked = true;
	}

	this->name = name ? *name : "";
}

