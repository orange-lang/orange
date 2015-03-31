/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

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

CastExpr::~CastExpr() {
	delete type;
	delete expr;
}