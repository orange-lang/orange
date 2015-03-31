#include "gen/ReturnExpr.h"
#include "gen/generator.h"
#include "gen/VarExpr.h"


Value* ReturnExpr::Codegen() {
	BasicBlock *bb = CG::Symtab->getFunctionEnd();
	if (expr) {
		Value *v = expr->Codegen();

		if (dynamic_cast<VarExpr*>(expr)) {
			v = CG::Builder.CreateLoad(v);
		}

		CG::Builder.CreateStore(v, CG::Symtab->retVal);
		Value *r = CG::Builder.CreateBr(bb);
		return r; 
	} else {
		return CG::Builder.CreateBr(bb);
	}
}
