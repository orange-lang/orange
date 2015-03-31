/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

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