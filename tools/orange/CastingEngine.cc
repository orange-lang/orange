/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/CastingEngine.h>
#include <orange/generator.h>

bool CastingEngine::AreTypesCompatible(Type* a, Type* b) {
	if (a == nullptr || b == nullptr) return false;

	if (a->getTypeID() == b->getTypeID()) return true; 
	if (a->isIntegerTy() && b->isFloatingPointTy()) return true;  
	if (b->isIntegerTy() && a->isFloatingPointTy()) return true;  
	if (a->isFloatingPointTy() && b->isFloatingPointTy()) return true;
	return false;
}

bool CastingEngine::CanTypeBeCasted(Type* src, Type* dest) {
	// For now, return the order-independent AreTypesCompatible
	return AreTypesCompatible(src, dest);
}

bool CastingEngine::CastValueToType(Value** v, Type* t, bool isSigned, bool force) {
	if (v == nullptr || t == nullptr) return false; 

	Type *srcType = (*v)->getType();

	// If we're not forcing, and we can't cast v to t, just return.
	if (force == false && CanTypeBeCasted(srcType, t) == false) return false;

	// If we're not forcing, and v has a higher precedence than t, return.
	if (force == false && ShouldTypeMorph(srcType, t) == false) return false; 

	// Here we're weeded out all unnecessary or impossible morphing; you don't have 
	// to check for force == true here anymore, so just morph anything that's possible.
	
	// Cast v to the integer type of t; this will account for bitwidths. 
	if (t->isIntegerTy() && srcType->isIntegerTy()) {
		*v = GE::builder()->CreateIntCast(*v, t, isSigned);
		return true;
	}

	if (t->isFloatingPointTy() && srcType->isFloatingPointTy()) {
		*v = GE::builder()->CreateFPCast(*v, t);
		return true;
	}

	if (t->isFloatingPointTy() && srcType->isIntegerTy()) {
		*v = isSigned ? GE::builder()->CreateSIToFP(*v, t) : GE::builder()->CreateUIToFP(*v, t);
		return true; 
	}

	if (t->isIntegerTy() && srcType->isFloatingPointTy()) {
		*v = isSigned ? GE::builder()->CreateFPToSI(*v, t) : GE::builder()->CreateFPToUI(*v, t);
		return true; 
	}

	if (t->isPointerTy() && srcType->isPointerTy()) {
		*v = GE::builder()->CreateBitCast(*v, t);
		return true; 
	}

	if (srcType->isPointerTy() && t->isIntegerTy()) {
		*v = GE::builder()->CreatePtrToInt(*v, t);
		return true; 
	}

	if (t->isPointerTy() && srcType->isPointerTy()) {
		*v = GE::builder()->CreateIntToPtr(*v, t); 
		return true;
	}


	throw std::runtime_error("could not determine type to cast.");
	return false;
}

bool CastingEngine::CastValuesToFit(Value** v1, Value** v2, bool isV1Signed, bool isV2Signed) {
	if (v1 == nullptr || v2 == nullptr) return false; 

	Type* type1 = (*v1)->getType();
	Type* type2 = (*v2)->getType();

	if (AreTypesCompatible(type1, type2) == false) return false;

	if (ShouldTypeMorph(type1, type2)) {
		// type2 > type1, so cast type1. 
		return CastValueToType(v1, type2, isV1Signed, false);
	} else {
		// type2 < type1, so cast type2.
		return CastValueToType(v2, type1, isV2Signed, false);
	}
}

bool CastingEngine::ShouldTypeMorph(Type* src, Type* dest) {
	if (dest->isFloatingPointTy() && src->isIntegerTy()) return true; 
	if (dest->isDoubleTy() && src->isFloatTy()) return true;

	if (src->isIntegerTy() && dest->isIntegerTy()) {
		return dest->getIntegerBitWidth() > src->getIntegerBitWidth();
	}

	return false;
}

Type* CastingEngine::GetFittingType(Type* v1, Type* v2) {
	if (AreTypesCompatible(v1, v2) == false) return nullptr; 
	return ShouldTypeMorph(v1, v2) ? v2 : v1; 
}