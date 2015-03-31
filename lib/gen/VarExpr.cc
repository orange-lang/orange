#include "gen/VarExpr.h"
#include "gen/generator.h"

Type *VarExpr::getType() {
	Symobj *o = CG::Symtab->find(name);

	if (o == nullptr) {
		std::cerr << "warning: " << name << " was not found in the symbol table " << CG::Symtab->ID << std::endl; 		
	}

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
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		exit(1);
	}	

	return o->isSigned;
}

Value* VarExpr::Codegen() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Fatal: no symbol " << name << " found.\n";
		return nullptr;
	}

	return o->getValue();
}