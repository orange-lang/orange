#include "gen/CastingEngine.h"
#include "gen/generator.h"

bool CastValueToType(Value **v, Type *t, bool isSigned, bool force) {
	if (v == nullptr || t == nullptr) {
		return false;
	}

	Type *changeType = (*v)->getType();

	if (t->isIntegerTy() && changeType->isIntegerTy()) {
		*v = CG::Builder.CreateIntCast(*v, t, isSigned);
		return true;
	}

	if (t->isFloatingPointTy() && changeType->isIntegerTy()) {
		if (isSigned) {
			*v = CG::Builder.CreateSIToFP(*v, t); 
		} else {
			*v = CG::Builder.CreateUIToFP(*v, t);
		}

		return true; 
	}

	if (t->isFloatingPointTy() && changeType->isFloatingPointTy()) {
		*v = CG::Builder.CreateFPCast(*v, t);
		return true;
	}

	if (force) {
		if (t->isIntegerTy() && changeType->isFloatingPointTy()) {
			if (isSigned) {
				*v = CG::Builder.CreateFPToSI(*v, t);
			} else {
				*v = CG::Builder.CreateFPToUI(*v, t);
			}
		} else {
			std::cerr << "fatal: can't determine type to force to.\n";
			changeType->dump(); printf("\n");
			t->dump(); printf("\n");
			exit(1);
		}
	}

	return false;
}

bool CastValuesToFit(Value **v1, Value **v2, bool isV1Signed, bool isV2Signed) {
	if (v1 == nullptr || v2 == nullptr) {
		return false;
	} 

	Type *typeV1 = (*v1)->getType();
	Type *typeV2 = (*v2)->getType();

	if (typeV1->isIntegerTy() && typeV2->isIntegerTy()) {
		bool ret = false;

		if (isV1Signed == true && isV2Signed == false) {
			// unsign v1 
			ret = CastValueToType(v1, typeV1, false);
			isV1Signed = false;
		} else if (isV1Signed == false && isV2Signed == true) {
			ret = CastValueToType(v2, typeV2, false);
			isV2Signed = false;
		}
	}

	bool b = false; 

	b = (CastValueToType(v1, GetFittingType(typeV1, typeV2), isV1Signed) ? true : b);
	b = (CastValueToType(v2, GetFittingType(typeV1, typeV2), isV2Signed) ? true : b);

	return b;
}

Type *GetFittingType(Type *v1, Type *v2) {
	if (v1 == nullptr || v2 == nullptr) {
		return nullptr;
	} 

	if (v1->isIntegerTy() && v2->isIntegerTy()) {
		if (v1->getIntegerBitWidth() > v2->getIntegerBitWidth()) {
			return v1;
		} else {
			return v2;
		}
	}

	if (v1->isFloatTy() && v2->isIntegerTy()) {
		return v1;
	} else if (v2->isFloatTy() && v1->isIntegerTy()) {
		return v2;
	}

	if (v1->isDoubleTy() && (v2->isIntegerTy() || v2->isFloatTy())) {
		return v1;
	} else if (v2->isDoubleTy() && (v1->isIntegerTy() || v1->isFloatTy())) {
		return v2;
	}

	if (v1->getTypeID() == v2->getTypeID()) {
		return v1; 
	}

	std::cerr << "WARNING: could not determine fitting type for the following:\n";
	v1->dump(); std::cerr << " and "; 
	v2->dump(); std::cerr << std::endl; 
	return nullptr;
}