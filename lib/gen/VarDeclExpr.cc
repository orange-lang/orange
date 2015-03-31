#include <gen/VarDeclExpr.h>
#include <gen/generator.h>

Value* VarDeclExpr::Codegen() {
	Value *v = CG::Builder.CreateAlloca(getType());

	if (value != nullptr) {
		CG::Builder.CreateStore(value->Codegen(), v);
	}

	CG::Symtab->objs[name]->setValue(v);

	return v; 
}

VarDeclExpr::VarDeclExpr(AnyType *type, std::string *name, Expression *value) {
	if (type == nullptr) {
		std::cerr << "fatal: explicitly created variables require a type.\n";
		exit(1);
	}

	if (name == nullptr) {
		std::cerr << "fatal: trying to create a variable without a name.\n";
		exit(1); 
	}

	this->type = type; 
	this->name = *name; 
	this->value = value;

	CG::Symtab->create(this->name);
	CG::Symtab->objs[this->name]->setType(getType());
}
