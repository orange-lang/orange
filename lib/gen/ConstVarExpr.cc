/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <gen/ConstVarExpr.h>
#include <gen/generator.h>
#include <gen/CastingEngine.h>

Value* ConstVarExpr::Codegen() {
	Value *v = CG::Builder.CreateAlloca(getType());

	Value *store = value->Codegen();

	if (value->getClass() == "VarExpr" || value->getClass() == "IfStatement") {
		store = CG::Builder.CreateLoad(store);
	}

	bool storeIsPtrToArray = store->getType()->isPointerTy() && store->getType()->getPointerElementType()->isArrayTy(); 
	bool vIsArray = getType()->isArrayTy(); 

	if (vIsArray && storeIsPtrToArray) {
		store = CG::Builder.CreateLoad(store);
	}

	CastValueToType(&store, getType(), value->isSigned(), true);
		
	CG::Builder.CreateStore(store, v);

	CG::Symtabs.top()->create(name);
	CG::Symtabs.top()->objs[name]->setValue(v);
	CG::Symtabs.top()->objs[name]->isLocked = true;
	CG::Symtabs.top()->objs[name]->isConst = true;

	return v; 
}

void ConstVarExpr::resolve() {
	if (resolved)
		return;

	if (value)
		value->resolve();

	CG::Symtabs.top()->create(name);
	CG::Symtabs.top()->objs[name]->setType(getType()->getPointerTo());
	CG::Symtabs.top()->objs[name]->isLocked = true;
	CG::Symtabs.top()->objs[name]->isConst = true;


	resolved = true; 
}

ConstVarExpr::ConstVarExpr(AnyType *type, std::string *name, Expression *value) {
	if (name == nullptr) {
		std::cerr << "fatal: trying to create a variable without a name.\n";
		exit(1); 
	}

	if (type == nullptr) {
		this->type = AnyType::Create(value->getType());
	} else {
		this->type = type; 
	}

	this->name = *name; 
	this->value = value;

	CG::Symtabs.top()->create(this->name);
	CG::Symtabs.top()->objs[this->name]->setType(getType()->getPointerTo());
	CG::Symtabs.top()->objs[this->name]->isSigned = isSigned();
}

ConstVarExpr::~ConstVarExpr() {
	delete type;
	delete value;
}