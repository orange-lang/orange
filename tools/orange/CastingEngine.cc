/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CastingEngine.h>
#include <orange/generator.h>

bool CastingEngine::AreTypesCompatible(AnyType* a, AnyType* b) {
	if (a == nullptr || b == nullptr) return false;

	if (a->string() == b->string()) return true; 
	if (a->isIntegerTy() && b->isIntegerTy()) return true;
	if (a->isIntegerTy() && b->isFloatingPointTy()) return true;  
	if (b->isIntegerTy() && a->isFloatingPointTy()) return true;  
	if (a->isFloatingPointTy() && b->isFloatingPointTy()) return true;
	return false;
}

bool CastingEngine::CanTypeBeCasted(AnyType* src, AnyType* dest) {
	// For now, return the order-independent AreTypesCompatible
	return AreTypesCompatible(src, dest);
}

bool CastingEngine::CastValueToType(Value** v, AnyType* t, bool isSigned, bool force) {
	if (v == nullptr || t == nullptr) return false; 

	AnyType* srcType = new AnyType((*v)->getType(), false);
	Type* llvmT = t->getLLVMType();

	// If we're not forcing, and we can't cast v to t, just return.
	if (force == false && CanTypeBeCasted(srcType, t) == false) return false;

	// If we're not forcing, and v has a higher precedence than t, return.
	if (force == false && ShouldTypeMorph(srcType, t) == false) return false; 

	// Here we're weeded out all unnecessary or impossible morphing; you don't have 
	// to check for force == true here anymore, so just morph anything that's possible.
	
	// Cast v to the integer type of t; this will account for bitwidths. 
	if (t->isIntegerTy() && srcType->isIntegerTy()) {
		*v = GE::builder()->CreateIntCast(*v, llvmT, isSigned);
		delete srcType;
		return true;
	}

	if (t->isFloatingPointTy() && srcType->isFloatingPointTy()) {
		*v = GE::builder()->CreateFPCast(*v, llvmT);
		delete srcType;
		return true;
	}

	if (t->isFloatingPointTy() && srcType->isIntegerTy()) {
		*v = isSigned ? GE::builder()->CreateSIToFP(*v, llvmT) : GE::builder()->CreateUIToFP(*v, llvmT);
		delete srcType;
		return true; 
	}

	if (t->isIntegerTy() && srcType->isFloatingPointTy()) {
		*v = isSigned ? GE::builder()->CreateFPToSI(*v, llvmT) : GE::builder()->CreateFPToUI(*v, llvmT);
		delete srcType;
		return true; 
	}

	if (t->isPointerTy() && srcType->isPointerTy()) {
		*v = GE::builder()->CreateBitCast(*v, llvmT);
		delete srcType;
		return true; 
	}

	if (srcType->isPointerTy() && t->isIntegerTy()) {
		*v = GE::builder()->CreatePtrToInt(*v, llvmT);
		delete srcType;
		return true; 
	}

	if (t->isPointerTy() && srcType->isPointerTy()) {
		*v = GE::builder()->CreateIntToPtr(*v, llvmT); 
		delete srcType;
		return true;
	}


	std::cout << t->string() << std::endl;
	std::cout << srcType->string() << std::endl;
	t->getLLVMType()->dump();
	srcType->getLLVMType()->dump();
	throw std::runtime_error("could not determine type to cast.");
	return false;
}

bool CastingEngine::CastValuesToFit(Value** v1, Value** v2, bool isV1Signed, bool isV2Signed) {
	if (v1 == nullptr || v2 == nullptr) return false; 

	AnyType* type1 = new AnyType((*v1)->getType(), isV1Signed);
	AnyType* type2 = new AnyType((*v2)->getType(), isV2Signed);

	if (AreTypesCompatible(type1, type2) == false) return false;

	bool retVal = false;

	if (ShouldTypeMorph(type1, type2)) {
		// type2 > type1, so cast type1. 
		retVal = CastValueToType(v1, type2, isV1Signed, false);
	} else {
		// type2 < type1, so cast type2.
		retVal = CastValueToType(v2, type1, isV2Signed, false);
	}

	delete type1; 
	delete type2;
	return retVal;
}

bool CastingEngine::ShouldTypeMorph(AnyType* src, AnyType* dest) {
	if (dest->isFloatingPointTy() && src->isIntegerTy()) return true; 
	if (dest->isDoubleTy() && src->isFloatTy()) return true;

	if (src->isIntegerTy() && dest->isIntegerTy()) {
		return dest->getIntegerBitWidth() > src->getIntegerBitWidth();
	}

	return false;
}

AnyType* CastingEngine::GetFittingType(AnyType* v1, AnyType* v2) {
	if (AreTypesCompatible(v1, v2) == false) return nullptr; 
	return ShouldTypeMorph(v1, v2) ? v2 : v1; 
}