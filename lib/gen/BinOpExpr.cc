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
	} else {
		std::cerr << "Fatal: can't determined if expression is signed!\n";
	}
	
	return false;
}


BinOpExpr::BinOpExpr(Expression *LHS, char op, Expression *RHS) {
	this->LHS = LHS;
	this->op = op;
	this->RHS = RHS;
}

Type *BinOpExpr::getType() { 
	if (LHS->getType() == RHS->getType()) {
		return LHS->getType(); 
	} else {
		std::cerr << "fatal: binop LHS and RHS have different types.\n";
		exit(1);
		return nullptr; 
	}

	return nullptr; 
}


Value* BinOpExpr::Codegen() {
	Value *L = LHS->Codegen();

	if (op == '=' && L == nullptr) {
		printf("((TODO: CREATE VARIABLE. FATAL.))\n");
	}

	Value *R = RHS->Codegen();
  if (dynamic_cast<VarExpr*>(RHS)) {
  	R = CG::Builder.CreateLoad(R, ((VarExpr*)RHS)->name);
  }

	if (!L || !R) return nullptr;

	switch (op) {
		case '+':
	 	case '-':
	 	case '*':
	 	case '/':
		  if (dynamic_cast<VarExpr*>(LHS)) {
		  	L = CG::Builder.CreateLoad(L, ((VarExpr*)LHS)->name);
		  }
		  break;
	}

	switch (op) {
		case '+':
			return CG::Builder.CreateAdd(L, R);
		case '-':
			return CG::Builder.CreateSub(L, R);
		case '*':
			return CG::Builder.CreateMul(L, R);
		case '/':
			// if one of them is signed, they're both signed.
			if (isSigned(LHS) || isSigned(RHS)) {
				return CG::Builder.CreateSDiv(L, R);
			} else {
				return CG::Builder.CreateUDiv(L, R);
			}
			
			return CG::Builder.CreateSDiv(L, R);
		case '=':
			return CG::Builder.CreateStore(R, L);
		default:
			printf("Unhandled: %c\n", op);
			return nullptr;
	}

	return nullptr;
}