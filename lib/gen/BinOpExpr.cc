#include "gen/BinOpExpr.h"
#include "gen/generator.h"
#include "gen/VarExpr.h"
#include "gen/Values.h"

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
		return isSigned(BOE->LHS) || isSigned(BOE->RHS);  
	} else {
		std::cerr << "Fatal: can't determined if expression is signed!\n";
		exit(1);
	}
	
	return false;
}


BinOpExpr::BinOpExpr(Expression *LHS, std::string op, Expression *RHS) {
	this->LHS = LHS;
	this->op = op;
	this->RHS = RHS;

	if (op == "=" && LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;

		CG::Symtab->create(L->name);
		CG::Symtab->objs[L->name]->setType(RHS->getType());
	}
}

Type *BinOpExpr::getType() { 
	if (LHS->getType() == RHS->getType()) {
		if (op == "<" || op == ">" || op == "<=" || op == ">=") {
			return Type::getInt1Ty(getGlobalContext());
		} 


		return LHS->getType(); 
	} else {
		if (LHS->getType()->getIntegerBitWidth() > RHS->getType()->getIntegerBitWidth()) {
			return LHS->getType(); 
		} else {
			return RHS->getType();
		}
	}

	return nullptr; 
}

Value* BinOpExpr::Codegen() {
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

	if (op != "=" && LHS->getClass() == "VarExpr") {
		// If it's a variable load it in. 
		L = CG::Builder.CreateLoad(L, ((VarExpr*)LHS)->name);
	}


	Value *R = RHS->Codegen();
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

	if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy()) {
		if (L->getType()->getIntegerBitWidth() != R->getType()->getIntegerBitWidth()) {

			// cast to highest 
			if (L->getType()->getIntegerBitWidth() > R->getType()->getIntegerBitWidth()) {
				// cast R to L 
				R = CG::Builder.CreateIntCast(R, L->getType(), false);
			} else {
				// cast L to R 
				L = CG::Builder.CreateIntCast(L, R->getType(), false);
			}
		}
	}


	if (op == "+") {
		return CG::Builder.CreateAdd(L, R);
	}
	else if (op == "-") {
		return CG::Builder.CreateSub(L, R);
	}
	else if (op == "*") {
		return CG::Builder.CreateMul(L, R);
	}
	else if (op == "/") {
		// if one of them is signed, they're both signed.
		if (isSigned(LHS) || isSigned(RHS)) {
			return CG::Builder.CreateSDiv(L, R);
		} else {
			return CG::Builder.CreateUDiv(L, R);
		}
			
		return CG::Builder.CreateSDiv(L, R);
	}
	else if (op == "=") {
		return CG::Builder.CreateStore(R, L);
	} 
	else if (op == "<") {
		Value *v;
		if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSLT(L, R);
		} else {
			v = CG::Builder.CreateICmpULT(L, R);
		}

		return v;
	} 
	else if (op == "<=") {
		Value *v;
		if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSLE(L, R);
		} else {
			v = CG::Builder.CreateICmpULE(L, R);
		}

		return v;
	}
	else if (op == ">") {
		Value *v;
		if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSGT(L, R);
		} else {
			v = CG::Builder.CreateICmpUGT(L, R);
		}

		return v;
	}
	else if (op == ">=") {
		Value *v;
		if (isSigned(LHS) || isSigned(RHS)) {
			v = CG::Builder.CreateICmpSGE(L, R);
		} else {
			v = CG::Builder.CreateICmpUGE(L, R);
		}

		return v;
	}
	else {
		std::cerr << "fatal: operation " << op << " does not have a generation case.";
		exit(1);
	}

	std::cerr << "fatal: incorrectly reached end of BinOpExpr generation.\n";
	exit(1);
	return nullptr;
}