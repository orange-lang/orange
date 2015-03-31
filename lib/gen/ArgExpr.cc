#include "gen/ArgExpr.h"
#include "gen/generator.h"

ArgExpr::ArgExpr(AnyType* type, std::string* name) {
	this->type = type;
	this->name = name ? *name : "";
	
	// if it's not u, then it's signed
	if (this->type && (this->type->type)[0] == 'u') {
		isSigned = false;
	} else isSigned = true;

	CG::Symtab->create(this->name);
	if (this->type) {
		CG::Symtab->objs[this->name]->setType(this->type->getType());
	}
	CG::Symtab->objs[this->name]->isSigned = isSigned;
}

