#include "gen/ArgExpr.h"
#include "gen/generator.h"

ArgExpr::ArgExpr(AnyType* type, std::string* name) {
	this->type = type;
	this->name = name ? *name : "";
}

