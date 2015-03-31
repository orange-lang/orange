#include "gen/ReturnExpr.h"
#include "gen/generator.h"
#include "gen/VarExpr.h"


Value* ReturnExpr::Codegen() {
	DEBUG_MSG("GENERATING ReturnExpr");

	BasicBlock *bb = CG::Symtab->getFunctionEnd();
	if (bb == nullptr) {
		std::cerr << "fatal: no Function End found!\n";
		exit(1);
	}

	if (expr) {
		Value *v = expr->Codegen();

		if (expr->getClass() == "VarExpr") {
			v = CG::Builder.CreateLoad(v);
		}
		
		CG::TheModule->dump();

		CG::Builder.CreateStore(v, CG::Symtab->retVal);
		Value *r = CG::Builder.CreateBr(bb);
		return r; 
	} else {
		Value *r = CG::Builder.CreateBr(bb);
		return r;
	}
}
