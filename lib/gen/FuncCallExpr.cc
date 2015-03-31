#include "gen/generator.h"
#include "gen/Symtab.h"
#include "gen/ArgExpr.h"
#include "gen/Block.h"
#include "gen/Values.h"
#include "gen/FunctionStatement.h"
#include "gen/FuncCallExpr.h"

Type *FuncCallExpr::getType() {
	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr) {
		std::cerr << "Error: couldn't find " << name << " in symtab\n";
		return nullptr; 
	}

	if (o->reference == nullptr) {
		std::cerr << "Fatal: no reference for function object\n";
		return nullptr; 
	}

	for (auto obj : CG::Symtab->objs) {
		std::cout << obj.first << std::endl;
	}

	if (o->getValue() && isa<Function>(o->getValue())) {
		Function *f = (Function *)o->getValue();
		return f->getReturnType();
	}

	if (o->getValue() == nullptr && o->reference->getClass() == "FunctionStatement") { 
		FunctionStatement *fstmt = (FunctionStatement *)o->reference;
		return fstmt->body->getReturnType();
	}

	if (o->getType()) {
		return o->getType();
	}

	std::cerr << "Error: couldn't return anything for FuncCallExpr\n"; 
	return nullptr; 
}

Value* FuncCallExpr::Codegen() {
	std::vector<Value*> Args(args->size());
	for (unsigned int i = 0; i < args->size(); i++) {
		auto arg = (*args)[i];
		Args[i] = arg->Codegen();

		if (arg->getClass() == "VarExpr") {
			Args[i] = CG::Builder.CreateLoad(Args[i]);
		}
	}

	Symobj *o = CG::Symtab->find(name);
	if (o == nullptr || o->getValue() == nullptr) {
		std::cerr << "Error: no function called " << name << " found.";
		return nullptr;
	}

	if (isa<Function>(o->getValue())) {
		Function *f = cast<Function>(o->getValue());
		// const auto fargs = f->getArgumentList();
		if (f->isVarArg() == false && f->arg_size() != args->size()) {
			std::cerr << "Fatal: function arguments do not match number of arguments in callee\n";
			exit(1);
		}

		int i = 0;
		for (auto it = f->arg_begin(); it != f->arg_end(); ++it, ++i) {
			Value *arg = it;
			auto larg = (*args)[i];

			bool isSigned = false; 
			if (dynamic_cast<IntVal *>(larg)) {
				isSigned = true;
			}

			Args[i] = CG::Builder.CreateIntCast(Args[i], arg->getType(), isSigned);
		}
	}

	Value *v = CG::Builder.CreateCall(o->getValue(), Args);
	return v;
}