#include "gen/AnyType.h"
#include "gen/Values.h"

AnyType* AnyType::clone() {
	AnyType* ret = new AnyType;
	for (auto n : arrays) ret->arrays.push_back(n);
	ret->type = type;
	ret->numPointers = numPointers;
	return ret;
}

std::string AnyType::string(bool no_brackets) {
	std::stringstream ss;
	ss << type;

	for (int i = 0; i < numPointers; i++) {
		ss << "*";
	}

	if (arrays.size() > 0) {
		for (auto sz : arrays) {
			if (no_brackets == false) {
				ss << "[" << sz << "]"; 
			} else {
				ss << "_" << sz; 
			}
		}
	}

	return ss.str();
}

AnyType *AnyType::Create(Type *t) {
	AnyType *ret = new AnyType;
	ret->numPointers = 0;

	while (t->isPointerTy()) {
		ret->numPointers++;
		t = t->getPointerElementType();
	}

	if (t->isFloatTy()) {
		ret->type = "float"; 
	} else if (t->isDoubleTy()) {
		ret->type = "double";
	} else if (t->isIntegerTy(8)) {
		ret->type = "int8";
	} else if (t->isIntegerTy(16)) {
		ret->type = "int16"; 
	} else if (t->isIntegerTy(32)) {
		ret->type = "int32";
	} else if (t->isIntegerTy(64)) {
		ret->type = "int64";
	} else if (t->isVoidTy()) {
		ret->type = "void";
	}

	Type *t_ptr = t; 

	while (t_ptr->isArrayTy()) {
		ArrayType *at = (ArrayType *)t;
		ret->arrays.push_back((int)at->getNumElements());
		t_ptr = t_ptr->getArrayElementType();		
	}

	return ret;
}

bool AnyType::isSigned() {
	return (type[0] == 'i');
}

int AnyType::absoluteNumPtrs() {
	int ret = numPointers + arrays.size();
	ret += arrays.size();
	return ret;
}


Type *AnyType::getType() {
	Type *initial = ::getType(type);

	for (int i = 0; i < numPointers; i++) {
		initial = initial->getPointerTo(0);
	}

	if (arrays.size() > 0) {
		for (int i = arrays.size() - 1; i >= 0; i--) {
			initial = ArrayType::get(initial, arrays[i]);
		}
	}

	return initial;
}

AnyType::AnyType(std::string *type, int numPointers, std::vector<BaseVal *> *arrays) {
	this->type = *type;
	this->numPointers = numPointers; 

	if (arrays == nullptr) { 
		return; 
	}

	for (BaseVal *bv : *arrays) {
		if (bv == nullptr) {
			this->numPointers++;
			continue;
		}

		if (bv->getClass() != "UIntVal" && bv->getClass() != "IntVal") {
			std::cerr << "fatal: cannot construct array with element size " << bv->string() << std::endl;
			exit(1);
		}

		if (bv->getClass() == "UIntVal") {
			UIntVal *uiv = (UIntVal *)bv; 
			this->arrays.push_back(uiv->value); 
		} else if (bv->getClass() == "IntVal") {
			IntVal *iv = (IntVal *)bv; 
			this->arrays.push_back((uint64_t)iv->value);
		}
	}
}

