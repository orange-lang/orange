#include "gen/BinOpExpr.h"
#include "gen/generator.h"
#include "gen/VarExpr.h"
#include "gen/Values.h"
#include "gen/FuncCallExpr.h"
#include "gen/CastingEngine.h"

bool isCmpOperator(std::string op) {
	return op == ">" || op == ">=" || op == "<" ||
		op == "<=" || op == "==" || op == "!=";
}

bool isAssignOperator(std::string op) {
	return op == "=" || op == "+=" || op == "-=" || 
		op == "*=" || op == "/=" || op == "<-";
}

bool BinOpExpr::isSigned() {
	if (isCmpOperator(op)) {
		return false; 
	}

	if (op == "&&" || op == "||") {
		return false;
	}

	return LHS->isSigned() && RHS->isSigned();
}

void BinOpExpr::resolve() {
	if (resolved)
		return;

	LHS->resolve();
	RHS->resolve();
	
	if (op == "=" && LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;

		// If it doesn't exist, then create it 
		if (CG::Symtabs.top()->find(L->name) == nullptr) {
			CG::Symtabs.top()->create(L->name);
			CG::Symtabs.top()->objs[L->name]->setType(RHS->getType()->getPointerTo());
		}
	} else if (op == "<-" && LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;

		// Create it, regardless of whether it exists in a parent scope.		
		CG::Symtabs.top()->create(L->name);
		CG::Symtabs.top()->objs[L->name]->setType(RHS->getType()->getPointerTo());
	} else if (LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;

		if (CG::Symtabs.top()->find(L->name) == nullptr) {

			std::cerr << "fatal: variable " << L->name << " not found\n";
			exit(1);
		}
		
	}

	Type *LType = LHS->getType();
	Type *RType = RHS->getType();

	// Do data morphing on unlocked variables here.
	if (isAssignOperator(op) && LHS->getClass() == "VarExpr") {
		VarExpr *L = (VarExpr *)LHS;
		Symobj *obj = CG::Symtabs.top()->find(L->name);

		if (obj->isConst == true) {
			std::cerr << "error: trying to assign to constant variable " << L->name << std::endl;
			exit(1);
		}

		if (obj->isLocked == false && ShouldTypesMorph(LType, RType)) {
			obj->setType(RType->getPointerTo());
		}
	} 

	resolved = true;
}

BinOpExpr::BinOpExpr(Expression *LHS, std::string op, Expression *RHS) {
	this->LHS = LHS;
	this->op = op;
	this->RHS = RHS;
}

Type *BinOpExpr::getType() { 
	DEBUG_MSG("((BinOpExpr)) GETTING TYPE OF " << LHS->string() << " " << op << " " << RHS->string());

	if (isCmpOperator(op)) {
		return Type::getInt1Ty(getGlobalContext());
	} 

	// If LHS or RHS is a call to the function we're currently inside, return nullptr, hoping we'll 
	// be resolved later. 
	if (LHS->getClass() == "FuncCallExpr") {
		std::string currFunction = CG::Symtabs.top()->getFunctionName();

		FuncCallExpr *fexpr = (FuncCallExpr *)LHS; 
		if (fexpr->name == currFunction) 
			return nullptr; 		
	}

	if (RHS->getClass() == "FuncCallExpr") {
		std::string currFunction = CG::Symtabs.top()->getFunctionName();
	
		FuncCallExpr *fexpr = (FuncCallExpr *)RHS; 
		if (fexpr->name == currFunction) 
			return nullptr; 				
	}

	if (isAssignOperator(op)) {
		Type *t = LHS->getType(); 
		if (t == nullptr) {
			return RHS->getType();
		}

		return t; 
	}

	Type *L = LHS->getType();
	Type *R = RHS->getType();

	if (!L || !R) {
		// Return null, hoping this will be resolved later.
		return nullptr; 
	}

	Type *T = GetFittingType(L, R);
	return T;
}

Value* BinOpExpr::Codegen() {
	Value *L = LHS->Codegen();

	// We want to create the variable here instead of in LHS->Codegen,
	// since LHS->Codegen would create a nonexistant variable on the RHS potentially 
	if ((op == "=" || op == "<-") && L == nullptr) {
		L = CG::Builder.CreateAlloca(LHS->getType());
		VarExpr *vLHS = (VarExpr *)LHS;

		if (CG::Symtab()->objs[vLHS->name] == nullptr) {
			std::cerr << "fatal: variable " << vLHS->name << " is not in the symtab.\n";
			exit(1);
		}

		CG::Symtabs.top()->objs[vLHS->name]->setValue(L);
	}

	if (L == nullptr) {
		std::cerr << "fatal: LHS of expression has returned null!\n";
		exit(1);
	}

	Value *OrigL = L;
	if ((op != "=" && op != "<-") && LHS->returnsPtr()) {
		// If it's a variable load it in. 
		L = CG::Builder.CreateLoad(L, "var");
	}

	Value *R = RHS->Codegen();
	Value *OrigR = R;

	if (R == nullptr) {
		std::cerr << "fatal: RHS of expression has returned null!\n";
		exit(1);
	}
	
	if (RHS->returnsPtr()) {
		// If it's a variable load it in. 
		R = CG::Builder.CreateLoad(R);
	}

	if (!L || !R) {
		std::cerr << "fatal: generating BinOpExpr failed.\n";
		exit(1);
	}

	CastValuesToFit(&L, &R, LHS->isSigned(), RHS->isSigned());

	bool FPOperation = L->getType()->isFloatingPointTy() && R->getType()->isFloatingPointTy();
	bool isPtrOperation = L->getType()->isPointerTy() || R->getType()->isPointerTy(); 

	if (op == "/" && L->getType()->isFloatingPointTy() != R->getType()->isFloatingPointTy()) {
		std::cerr << "fatal: trying to perform operation " << op 
			<< " with only one of the operands being a floating point value.\n";
		exit(1);
	}

	if (isPtrOperation && op != "=" && op != "<-") {

		if (L->getType()->isFloatingPointTy() || R->getType()->isFloatingPointTy()) {
			std::cerr << "error: trying to perform binary operation with a pointer and float.\n";
			exit(1); 
		}

		if (isAssignOperator(op) && L->getType()->isPointerTy() == false) {
			std::cerr << "error: cannot assign pointer to non-pointer.\n";
			exit(1);
		} 

		if (op == "+") {
			// turn the pointer into an integer 
			Type *ptrType = L->getType()->isPointerTy() ? L->getType() : R->getType(); 

			if (L->getType()->isPointerTy()) 
				L = CG::Builder.CreatePointerCast(L, IntegerType::get(getGlobalContext(), 64));
			else 
				R = CG::Builder.CreatePointerCast(R, IntegerType::get(getGlobalContext(), 64));

			Value *sum = CG::Builder.CreateAdd(L, R);
			sum = CG::Builder.CreateIntToPtr(sum, ptrType);
			return sum;
		} else if (op == "-") {
			// turn the pointer into an integer 
			Type *ptrType = L->getType()->isPointerTy() ? L->getType() : R->getType(); 

			if (L->getType()->isPointerTy()) 
				L = CG::Builder.CreatePointerCast(L, IntegerType::get(getGlobalContext(), 64));
			else 
				R = CG::Builder.CreatePointerCast(R, IntegerType::get(getGlobalContext(), 64));

			Value *difference = CG::Builder.CreateSub(L, R);
			difference = CG::Builder.CreateIntToPtr(difference, ptrType);
			return difference;
		} else if (op == "+=") {
			if (L->getType()->isPointerTy()) 
				L = CG::Builder.CreatePointerCast(L, IntegerType::get(getGlobalContext(), 64));
			else 
				R = CG::Builder.CreatePointerCast(R, IntegerType::get(getGlobalContext(), 64));

			Value *sum = CG::Builder.CreateAdd(L, R);
			sum = CG::Builder.CreateIntToPtr(sum, OrigL->getType()->getPointerElementType());
			CG::Builder.CreateStore(sum, OrigL);		
			return CG::Builder.CreateLoad(OrigL);	
		} else if (op == "-=") {
			if (L->getType()->isPointerTy()) 
				L = CG::Builder.CreatePointerCast(L, IntegerType::get(getGlobalContext(), 64));
			else 
				R = CG::Builder.CreatePointerCast(R, IntegerType::get(getGlobalContext(), 64));

			Value *difference = CG::Builder.CreateSub(L, R);
			difference = CG::Builder.CreateIntToPtr(difference, OrigL->getType()->getPointerElementType());
			CG::Builder.CreateStore(difference, OrigL);		
			return CG::Builder.CreateLoad(OrigL);	
		} else {
			std::cerr << "fatal: trying to perform invalid binary operation " << op << " on a pointer\n";
			exit(1);
		}
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

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), LHS->isSigned(), true);

		CG::Builder.CreateStore(v, OrigL);		
		return CG::Builder.CreateLoad(OrigL);	
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

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), LHS->isSigned(), true);

		CG::Builder.CreateStore(v, OrigL);	
		return CG::Builder.CreateLoad(OrigL);		
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

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), LHS->isSigned(), true);

		CG::Builder.CreateStore(v, OrigL);		
		return CG::Builder.CreateLoad(OrigL);	
	}	
	else if (op == "/") {
		// if one of them is signed, they're both signed.
		if (FPOperation) {
			return CG::Builder.CreateFDiv(L, R);
		} else {
			if (isSigned()) {
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
		} else if (isSigned()) {
			v = CG::Builder.CreateSDiv(L, R);
		} else {
			v = CG::Builder.CreateUDiv(L, R);
		}

		CastValueToType(&v, OrigL->getType()->getPointerElementType(), LHS->isSigned(), true);

		CG::Builder.CreateStore(v, OrigL);	
		return CG::Builder.CreateLoad(OrigL);	
	}


	else if (op == "%") {
		if (FPOperation) {
			return CG::Builder.CreateFRem(L, R);
		} else {
			if (isSigned()) {
				return CG::Builder.CreateSRem(L, R);
			} else {
				return CG::Builder.CreateURem(L, R);
			}
		}		
	}
	else if (op == "&") {
		return CG::Builder.CreateAnd(L, R);
	} 
	else if (op == "|") {
		return CG::Builder.CreateOr(L, R);
	}
	else if (op == "^") {
		return CG::Builder.CreateXor(L, R);
	}


	else if (op == "=" || op == "<-") {
		CastValueToType(&R, OrigL->getType()->getPointerElementType(), LHS->isSigned());

		Value *v = CG::Builder.CreateStore(R, L);
		return CG::Builder.CreateLoad(L);
	} 
	else if (op == "<") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOLT(L, R);
		} else if (isSigned()) {
			v = CG::Builder.CreateICmpSLT(L, R);
		} else {
			v = CG::Builder.CreateICmpULT(L, R);
		}

		return v;
	} 
	else if (op == "<=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOLE(L, R);
		} else if (isSigned()) {
			v = CG::Builder.CreateICmpSLE(L, R);
		} else {
			v = CG::Builder.CreateICmpULE(L, R);
		}

		return v;
	}
	else if (op == ">") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOGT(L, R);
		} else if (isSigned()) {
			v = CG::Builder.CreateICmpSGT(L, R);
		} else {
			v = CG::Builder.CreateICmpUGT(L, R);
		}

		return v;
	}
	else if (op == ">=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOGE(L, R);
		} else if (isSigned()) {
			v = CG::Builder.CreateICmpSGE(L, R);
		} else {
			v = CG::Builder.CreateICmpUGE(L, R);
		}

		return v;
	}
	else if (op == "==") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpOEQ(L, R);
		} else {
			v = CG::Builder.CreateICmpEQ(L, R);
		}		

		return v;
	}
	else if (op == "!=") {
		Value *v = nullptr;
		if (FPOperation) {
			v = CG::Builder.CreateFCmpONE(L, R);
		} else {
			v = CG::Builder.CreateICmpNE(L, R);
		}			

		return v;
	}
	else if (op == "&&") {
		Type *boolean = IntegerType::get(getGlobalContext(), 1);
		Value *v = CG::Builder.CreateAlloca(boolean);
		CastValueToType(&L, boolean, false, true);
		CG::Builder.CreateStore(L, v);

		auto _Function = CG::Symtabs.top()->getFunction(); 
		auto _FunctionEnd = CG::Symtabs.top()->getFunctionEnd();		

		BasicBlock *CheckBlock = BasicBlock::Create(getGlobalContext(), "check", _Function, _FunctionEnd);
		BasicBlock *ContinueBlock = BasicBlock::Create(getGlobalContext(), "continue", _Function, _FunctionEnd);

		// If LHS is false, go to continue, else go to check.
		// in check: v = RHS
		// continue: return v 
		CG::Builder.CreateCondBr(L, CheckBlock, ContinueBlock);				
		CG::Builder.SetInsertPoint(CheckBlock);
		CastValueToType(&R, boolean, false, true);
		CG::Builder.CreateStore(R, v);
		CG::Builder.CreateBr(ContinueBlock);
		CG::Builder.SetInsertPoint(ContinueBlock);
		v = CG::Builder.CreateLoad(v);

		return v;
	}
	else if (op == "||") {
		Type *boolean = IntegerType::get(getGlobalContext(), 1);
		Value *v = CG::Builder.CreateAlloca(boolean);
		CastValueToType(&L, boolean, LHS->isSigned(), true);
		CG::Builder.CreateStore(L, v);

		auto _Function = CG::Symtabs.top()->getFunction(); 
		auto _FunctionEnd = CG::Symtabs.top()->getFunctionEnd();		

		BasicBlock *CheckBlock = BasicBlock::Create(getGlobalContext(), "check", _Function, _FunctionEnd);
		BasicBlock *ContinueBlock = BasicBlock::Create(getGlobalContext(), "continue", _Function, _FunctionEnd);

		// If LHS is false, go to continue, else go to check.
		// in check: v = RHS
		// continue: return v 
		CG::Builder.CreateCondBr(L, ContinueBlock, CheckBlock);				
		CG::Builder.SetInsertPoint(CheckBlock);
		CastValueToType(&R, boolean, LHS->isSigned(), true);
		CG::Builder.CreateStore(R, v);
		CG::Builder.CreateBr(ContinueBlock);
		CG::Builder.SetInsertPoint(ContinueBlock);
		v = CG::Builder.CreateLoad(v);

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

BinOpExpr::~BinOpExpr() {
	delete LHS;
	delete RHS;
}