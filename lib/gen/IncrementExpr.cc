#include "gen/IncrementExpr.h"
#include "gen/generator.h"

std::string IncrementExpr::string() {
	return expr->string() + op; 
}

Type* IncrementExpr::getType() {
	return expr->getType();	
}

void IncrementExpr::resolve() {
	if (resolved)
		return;
	resolved = true; 

	expr->resolve();
}

Value* IncrementExpr::Codegen() {
	Value *e = expr->Codegen();

	if (returnsPtr(expr->getClass()) == false) {
		std::cerr << "fatal: trying to increment an invalid expression\n";
		exit(1);
	}

	Value *pre_v = CG::Builder.CreateLoad(e);
	bool isFP = pre_v->getType()->isFloatingPointTy();

	Value *oper;

	if (isFP) {
		double delta = (op == "++") ? 1.0 : -1.0;  
		oper = CG::Builder.CreateFAdd(pre_v, ConstantFP::get(pre_v->getType(), delta));
	} else {
		uint64_t delta = (op == "++") ? 1 : -1;  
		oper = CG::Builder.CreateAdd(pre_v, ConstantInt::get(pre_v->getType(), delta, true));
	}

	CG::Builder.CreateStore(oper, e);

	if (prefixIncrement) {
		return CG::Builder.CreateLoad(e);
	} else {
		return pre_v;
	}
}

IncrementExpr::IncrementExpr(Expression *expr, std::string op, bool prefixIncrement) {
	this->expr = expr;
	this->op = op;
	this->prefixIncrement = prefixIncrement;
}

