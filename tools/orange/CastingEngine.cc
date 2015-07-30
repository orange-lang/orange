/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CastingEngine.h>
#include <orange/generator.h>
#include <orange/AST.h>

bool CastingEngine::AreNodesCompatible(ASTNode* a, ASTNode* b) {
	if (a == nullptr || b == nullptr) {
		throw std::runtime_error("a and be must not be nullptr");
	}

	auto a_ty = a->getType();
	auto b_ty = b->getType(); 

	return AreTypesCompatible(a_ty, b_ty);
}

bool CastingEngine::IsNodeCompatible(ASTNode* a, OrangeTy* ty) {
	if (a == nullptr) {
		throw std::runtime_error("a must not be nullptr");
	}

	auto a_ty = a->getType();
	return AreTypesCompatible(a_ty, ty);
}

bool CastingEngine::AreTypesCompatible(OrangeTy* a_ty, OrangeTy* b_ty) {
	if (a_ty == nullptr || b_ty == nullptr) {
		throw std::runtime_error("a.type or b.type is nullptr");
	} 

	if (a_ty == b_ty) return true; 
	if (a_ty->isIntegerTy() && b_ty->isIntegerTy()) return true;
	if (a_ty->isFloatingPointTy() && b_ty->isFloatingPointTy()) return true;
	if (a_ty->isIntegerTy() && b_ty->isFloatingPointTy()) return true;  
	if (b_ty->isIntegerTy() && a_ty->isFloatingPointTy()) return true;  
	if (a_ty->isIntegerTy() && b_ty->isPointerTy()) return true; 
	if (b_ty->isIntegerTy() && a_ty->isPointerTy()) return true;
	return false;
}

bool CastingEngine::CanNodeBeCasted(ASTNode* src, ASTNode* dest) {
	return AreNodesCompatible(src, dest);
}

bool CastingEngine::CanNodeBeCasted(ASTNode* src, OrangeTy* ty) {
	return IsNodeCompatible(src, ty);
}

bool CastingEngine::CanTypesBeCasted(OrangeTy* ty1, OrangeTy* ty2) {
	return AreTypesCompatible(ty1, ty2);
}

bool CastingEngine::CastNode(ASTNode *from, ASTNode* to, bool force) {
	if (from == nullptr || to == nullptr) {
		throw std::runtime_error("from and to must not be nullptr");
	}

	auto to_ty = to->getType(); 

	if (to_ty == nullptr) {
		throw std::runtime_error("to.type is nullptr");
	} 

	return CastNode(from, to_ty);
}

bool CastingEngine::CastNode(ASTNode* from, OrangeTy* target, bool force) {
	if (from == nullptr || target == nullptr) {
		throw std::runtime_error("from and target must not be nullptr");
	}

	auto from_ty = from->getType();

	if (from_ty == nullptr) {
		throw std::runtime_error("from.type is nullptr");
	} 

	auto val = from->getValue();

	bool casted = CastValue(&val, from_ty, target, force);
	from->setValue(val);
	return casted;
}

bool CastingEngine::CastValue(Value** val, OrangeTy* from, OrangeTy* target, bool force) {
	if (val == nullptr || from == nullptr || target == nullptr) {
		throw std::runtime_error("val, from, and target must not be nullptr");
	}

	auto orig_val = *val;

	if (val == nullptr) {
		throw std::runtime_error("from has no value!");
	} 

	if (force == false && CanTypesBeCasted(from, target) == false) { 
		return false; 
	}

	if (from == target) {
		return true;
	}

	else if (from->isIntegerTy() && target->isIntegerTy()) {
		*val = GE::builder()->CreateIntCast(*val, target->getLLVMType(), from->isSigned());
	} 

	else if (from->isFloatingPointTy() && target->isFloatingPointTy()) {
		*val = GE::builder()->CreateFPCast(*val, target->getLLVMType());
	} 

	else if (from->isIntegerTy() && target->isFloatingPointTy()) {
		if (from->isSigned()) {
			*val = GE::builder()->CreateSIToFP(*val, target->getLLVMType());	
		} else {
			*val = GE::builder()->CreateUIToFP(*val, target->getLLVMType());	
		}
	} 

	else if (from->isFloatingPointTy() && target->isIntegerTy()) {
		if (from->isSigned()) {
			*val = GE::builder()->CreateFPToSI(*val, target->getLLVMType());
		} else {
			*val = GE::builder()->CreateFPToUI(*val, target->getLLVMType());
		}
	} 

	else if (from->isPointerTy() && target->isPointerTy()) {
		*val = GE::builder()->CreateBitCast(*val, target->getLLVMType());
	} 

	else if (from->isPointerTy() && target->isIntegerTy()) {
		*val = GE::builder()->CreatePtrToInt(*val, target->getLLVMType());
	} 

	else if (from->isIntegerTy() && target->isPointerTy()) {
		*val = GE::builder()->CreateIntToPtr(*val, target->getLLVMType());
	} 

	else if (from->isArrayTy() && target->isPointerTy()) {
		*val = GE::builder()->CreateBitCast(*val, target->getLLVMType());
	} 

	return *val != orig_val;
}


bool CastingEngine::CastToFit(ASTNode* n1, ASTNode* n2) {
	if (n1 == nullptr || n2 == nullptr) {
		throw std::runtime_error("n1 and n2 must not be nullptr");
	}

	switch (Compare(n1, n2)) {
		case LOWER_PRECEDENCE:
			return CastNode(n1, n2);
		case HIGHER_PRECEDENCE:
			return CastNode(n2, n1);
		case SAME_PRECEDENCE:
			return true; 
		case INCOMPATIBLE:
			return false;
	}

	return false;
}

bool CastingEngine::CastToFit(Value** v1, OrangeTy* ty1, Value** v2, OrangeTy* ty2) {
	if (v1 == nullptr || ty1 == nullptr || v2 == nullptr || ty2 == nullptr) {
		throw std::runtime_error("one or more arguments is nullptr");
	}

	switch (Compare(ty1, ty2)) {
		case LOWER_PRECEDENCE:
			return CastValue(v1, ty1, ty2);
		case HIGHER_PRECEDENCE:
			return CastValue(v2, ty2, ty1);
		case SAME_PRECEDENCE:
			return true; 
		case INCOMPATIBLE:
			return false;
	}

	return false;
}


PredenceComparison CastingEngine::Compare(ASTNode* n1, ASTNode* n2) {
	if (n1 == nullptr || n2 == nullptr) {
		throw std::runtime_error("n1 and n2 must not be nullptr");
	}

	auto n1_ty = n1->getType();
	auto n2_ty = n2->getType(); 

	return Compare(n1_ty, n2_ty);
}

PredenceComparison CastingEngine::Compare(ASTNode* n1, OrangeTy* ty) {
	if (n1 == nullptr || ty == nullptr) {
		throw std::runtime_error("n1 and ty must not be nullptr");
	}

	auto n1_ty = n1->getType();

	return Compare(n1_ty, ty);
}

PredenceComparison CastingEngine::Compare(OrangeTy* ty1, OrangeTy* ty2) {
	if (ty1 == nullptr || ty2 == nullptr) {
		throw std::runtime_error("ty1 or ty2 is nullptr");
	} 

	if (ty1 == ty2) return SAME_PRECEDENCE;
	else if (AreTypesCompatible(ty1, ty2) == false) return INCOMPATIBLE;
	else if (ty1->isIntegerTy() && ty2->isFloatingPointTy()) return LOWER_PRECEDENCE;
	else if (ty1->isFloatTy() && ty2->isDoubleTy()) return LOWER_PRECEDENCE;
	else if (ty1->isIntegerTy() && ty2->isIntegerTy()) {
		if (ty1->getIntegerBitWidth() < ty2->getIntegerBitWidth()) return LOWER_PRECEDENCE; 
		else if (ty1->getIntegerBitWidth() > ty2->getIntegerBitWidth()) return HIGHER_PRECEDENCE;
	}

	return HIGHER_PRECEDENCE;
}


ASTNode* CastingEngine::GetHighestPrecedence(ASTNode* n1, ASTNode* n2) {
	if (n1 == nullptr || n2 == nullptr) {
		throw std::runtime_error("n1 and n2 must not be nullptr");
	}

	switch (Compare(n1, n2)) {
		case LOWER_PRECEDENCE:
			return n2; 
		case HIGHER_PRECEDENCE:
		case SAME_PRECEDENCE:
			return n1; 
		case INCOMPATIBLE:
			return nullptr;
	}

	return nullptr;
}

OrangeTy* CastingEngine::GetHighestPrecedence(OrangeTy* ty1, OrangeTy* ty2) {
	if (ty1 == nullptr || ty2 == nullptr) {
		throw std::runtime_error("ty1 and ty2 must not be nullptr");
	}

	switch (Compare(ty1, ty2)) {
		case LOWER_PRECEDENCE:
			return ty2; 
		case HIGHER_PRECEDENCE:
		case SAME_PRECEDENCE:
			return ty1; 
		case INCOMPATIBLE:
			return nullptr;
	}

	return nullptr;
}
