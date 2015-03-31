#include "gen/CastExpr.h"
#include "gen/CastingEngine.h"
#include "gen/generator.h"

Value* CastExpr::Codegen() {
	Value *v = expr->Codegen(); 	

	if (expr->getClass() == "VarExpr") {
		v = CG::Builder.CreateLoad(v);
	}

	CastValueToType(&v, type->getType(), type->isSigned(), true);
	return v;
}
