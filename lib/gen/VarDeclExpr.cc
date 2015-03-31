#include <gen/VarDeclExpr.h>
#include <gen/generator.h>

Value* VarDeclExpr::Codegen() {
	DEBUG_MSG("GENERATING VarDeclExpr");

	Value *v = CG::Builder.CreateAlloca(getType());


	if (value != nullptr) {
		Value *store = value->Codegen();

		if (getType()->isIntegerTy() && store->getType()->isIntegerTy()) {
			if (getType()->getIntegerBitWidth() != store->getType()->getIntegerBitWidth()) {
				store = CG::Builder.CreateIntCast(store, getType(), type->isSigned());
			}
		}

		if (getType()->getTypeID() != store->getType()->getTypeID()) {
			// cast store to getType 
			if (getType()->isIntegerTy()) {
				if (store->getType()->isFloatingPointTy()) {
					if (type->isSigned()) {
						store = CG::Builder.CreateFPToSI(store, getType());						
					} else {
						store = CG::Builder.CreateFPToUI(store, getType());
					}
				} else {
					store = CG::Builder.CreateIntCast(store, getType(), type->isSigned()); 
				}
			} else if (getType()->isFloatingPointTy()) {
				store = CG::Builder.CreateFPCast(store, getType());				
			} 

		}

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
