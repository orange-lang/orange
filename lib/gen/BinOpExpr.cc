#include "gen/BinOpExpr.h"
#include "gen/generator.h"
#include "gen/VarExpr.h"
#include "gen/Values.h"
#include "gen/CastingEngine.h"

bool isCmpOperator(std::string op) {
	return op == ">" || op == ">=" || op == "<" ||
		op == "<=" || op == "==" || op == "!=";
}

bool isSigned(Expression *e) {
	if (dynamic_cast<IntVal*>(e)) {
		return true;
	} else if (dynamic_cast<UIntVal*>(e)) {
		return false;
	} else if (dynamic_cast<VarExpr*>(e)) {
		VarExpr *ve = (VarExpr *)e;
		Symobj* p = CG::Symtab->find(ve->name);
		return p->isSigned;
	} else if (e->getClass() == "BinOpExpr") {
		BinOpExpr *BOE = (BinOpExpr *)e; 

		if (isCmpOperator(BOE->op)) {
			return false;
		}

		return isSigned(BOE->LHS) || isSigned(BOE->RHS);  
	}
	
	return true;
}

BinOpExpr::BinOpExpr(Expression *LHS, std::string op, Expression *RHS) {
	DEBUG_MSG("STARTING BinOpExpr");

	this->LHS = LHS;
	this->op = op;
	this->RHS = RHS;

	if (op == "=" && LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;

		CG::Symtab->create(L->name);
		CG::Symtab->objs[L->name]->setType(RHS->getType());
	}

	DEBUG_MSG("COMPLETED BinOpExpr");
}

Type *BinOpExpr::getType() { 
	DEBUG_MSG("GETTING TYPE OF " << LHS->string() << " " << op << " " << RHS->string());

	if (isCmpOperator(op)) {
		return Type::getInt8Ty(getGlobalContext());
	} 

	return GetFittingType(LHS->getType(), RHS->getType());
}

Value* BinOpExpr::Codegen() {
	DEBUG_MSG("GENERATING BinOpExpr for " << LHS->string() << " " << op << " " << RHS->string());

	Value *L = LHS->Codegen();

	// We want to create the variable here instead of in LHS->Codegen,
	// since LHS->Codegen would create a nonexistant variable on the RHS potentially 
	if (op == "=" && L == nullptr) {
		L = CG::Builder.CreateAlloca(LHS->getType());
		CG::Symtab->objs[((VarExpr*)LHS)->name]->setValue(L);
	}

	if (L == nullptr) {
		std::cerr << "fatal: LHS of expression has returned null!\n";
		exit(1);
	}

	Value *OrigL = L;
	if (op != "=" && LHS->getClass() == "VarExpr") {
		// If it's a variable load it in. 
		L = CG::Builder.CreateLoad(L, ((VarExpr*)LHS)->name);
	}

	Value *R = RHS->Codegen();
	Value *OrigR = R;

	if (R == nullptr) {
		std::cerr << "fatal: RHS of expression has returned null!\n";
		exit(1);
	}

	if (RHS->getClass() == "VarExpr") {
		// If it's a variable load it in. 
		R = CG::Builder.CreateLoad(R, ((VarExpr*)RHS)->name);
	}

	if (!L || !R) {
		std::cerr << "fatal: generating BinOpExpr failed.\n";
		exit(1);
	}

	CastValuesToFit(&L, &R, isSigned(LHS), isSigned(RHS));

	bool FPOperation = false;
	if (L->getType()->isFloatingPointTy() && R->getType()->isFloatingPointTy()) {
		FPOperation = true;
	}

	if (op == "+") {
		if (FPOperation) {
			return CG::Builder.CreateFAdd(L, R);
		} else {
			return CG::Builder.CreateAdd(L, R);
		}
	}
	else if (op == "+=") {
		Value *v;
		if (FPOperation) {
			v = CG::Builder.CreateFAdd(L, R);
		} else {
			v = CG::Builder.CreateAdd(L, R);
		}	

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), isSigned(LHS) || isSigned(RHS));

		return CG::Builder.CreateStore(v, OrigL);		
	}
	else if (op == "-") {
		if (FPOperation) {
			return CG::Builder.CreateFSub(L, R);
		} else {
			return CG::Builder.CreateSub(L, R);
		}
	}
	else if (op == "-=") {
		Value *v;
		if (FPOperation) {
			v = CG::Builder.CreateFSub(L, R);
		} else {
			v = CG::Builder.CreateSub(L, R);
		}

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), isSigned(LHS) || isSigned(RHS));

		return CG::Builder.CreateStore(v, OrigL);		
	}	
	else if (op == "*") {
		if (FPOperation) {
			return CG::Builder.CreateFMul(L, R);
		} else {
			return CG::Builder.CreateMul(L, R);			
		}
	}
	else if (op == "*=") {
		Value *v; 
		if (FPOperation) {
			v = CG::Builder.CreateFMul(L, R);
		} else {
			v = CG::Builder.CreateMul(L, R);			
		}

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), isSigned(LHS) || isSigned(RHS));

		return CG::Builder.CreateStore(v, OrigL);		
	}	
	else if (op == "/") {
		// if one of them is signed, they're both signed.
		if (FPOperation) {
			return CG::Builder.CreateFDiv(L, R);
		} else {
			if (isSigned(LHS) || isSigned(RHS)) {
				return CG::Builder.CreateSDiv(L, R);
			} else {
				return CG::Builder.CreateUDiv(L, R);
			}
		}
	}
	else if (op == "/=") {
		Value *v;

		// if one of them is signed, they're both signed.
		if (FPOperation) {
			v = CG::Builder.CreateFDiv(L, R);
		} else if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateSDiv(L, R);
		} else {
			v = CG::Builder.CreateUDiv(L, R);
		}

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), isSigned(LHS) || isSigned(RHS));

		return CG::Builder.CreateStore(v, OrigL);		
	}

	else if (op == "=") {
		return CG::Builder.CreateStore(R, L);
	} 
	else if (op == "<") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOLT(L, R);
		} else if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSLT(L, R);
		} else {
			v = CG::Builder.CreateICmpULT(L, R);
		}

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);
	} 
	else if (op == "<=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOLE(L, R);
		} else if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSLE(L, R);
		} else {
			v = CG::Builder.CreateICmpULE(L, R);
		}

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);
	}
	else if (op == ">") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOGT(L, R);
		} else if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSGT(L, R);
		} else {
			v = CG::Builder.CreateICmpUGT(L, R);
		}

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);
	}
	else if (op == ">=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOGE(L, R);
		} else if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSGE(L, R);
		} else {
			v = CG::Builder.CreateICmpUGE(L, R);
		}

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);
	}
	else if (op == "==") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOEQ(L, R);
		} else {
			v = CG::Builder.CreateICmpEQ(L, R);
		}		

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);
	}
	else if (op == "!=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpONE(L, R);
		} else {
			v = CG::Builder.CreateICmpNE(L, R);
		}			

		return CG::Builder.CreateIntCast(v, Type::getInt8Ty(getGlobalContext()), false);	
	}
	else {
		std::cerr << "fatal: operation " << op << " does not have a generation case.";
		exit(1);
	}

	std::cerr << "fatal: incorrectly reached end of BinOpExpr generation.\n";
	exit(1);
	return nullptr;
}