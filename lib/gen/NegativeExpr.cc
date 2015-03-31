#include <gen/NegativeExpr.h>
#include <gen/generator.h>

Value* NegativeExpr::Codegen() {
	Value *v = expr->Codegen();

	if (expr->returnsPtr()) {
		v = CG::Builder.CreateLoad(v);
	}

	Type *t = v->getType();
	if (t->isFloatingPointTy()) {
		return CG::Builder.CreateFNeg(v);
	} else {
		return CG::Builder.CreateNeg(v);
	}
}

NegativeExpr::~NegativeExpr() {
	delete expr;
}