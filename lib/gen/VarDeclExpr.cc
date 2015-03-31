#include <gen/VarDeclExpr.h>
#include <gen/generator.h>
#include <gen/CastingEngine.h>

Value* VarDeclExpr::Codegen() {
	DEBUG_MSG("GENERATING VarDeclExpr");

	Value *v = CG::Builder.CreateAlloca(getType());

	if (value != nullptr) {
		Value *store = value->Codegen();

		if (value->getClass() == "VarExpr") {
			// If it's a variable load it in. 
			store = CG::Builder.CreateLoad(store);
		}

		CastValueToType(&store, getType(), value->isSigned(), true);
		CG::Builder.CreateStore(store, v);
	}

	CG::Symtab->objs[name]->setValue(v);

	return v; 
}

VarDeclExpr::VarDeclExpr(AnyType *type, std::string *name, Expression *value) {
	DEBUG_MSG("STARTING VarDeclExpr");

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

	DEBUG_MSG("COMPLETED VarDeclExpr");
}
