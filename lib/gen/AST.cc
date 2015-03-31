#include "gen/AST.h"
#include "gen/generator.h"
#include "gen/Values.h"
#include "gen/ArgExpr.h"
typedef CodeGenerator CG;

ArgList* ArgList::clone() {
	ArgList *ret = new ArgList; 
	for (ArgExpr *expr : *this) {
		ret->push_back((ArgExpr *)expr->clone());
	}
	return ret;
}

Value *replace(Value *del, Value *v) {
	delete del; 
	return v; 
}

Type *getType(std::string typeStr) {
	if (typeStr == "int" || typeStr == "int64") {
		return Type::getInt64Ty(getGlobalContext());
	} else if (typeStr == "int8" || typeStr == "char") {
		return Type::getInt8Ty(getGlobalContext());
	} else if (typeStr == "int16") {
		return Type::getInt16Ty(getGlobalContext());
	} else if (typeStr == "int32") {
		return Type::getInt32Ty(getGlobalContext());
	} else if (typeStr == "uint8") {
		return Type::getInt8Ty(getGlobalContext());
	} else if (typeStr == "uint16") {
		return Type::getInt16Ty(getGlobalContext());
	} else if (typeStr == "uint32") {
		return Type::getInt32Ty(getGlobalContext());
	} else if (typeStr == "uint" || typeStr == "uint64") {
		return Type::getInt64Ty(getGlobalContext());
	} else if (typeStr == "float") {
		return Type::getFloatTy(getGlobalContext());
	} else if (typeStr == "double") {
		return Type::getDoubleTy(getGlobalContext());
	} else {
		std::cerr << "FATAL: unknown type " << typeStr << "!\n";
	}

	return nullptr;
}

AnyType* AnyType::clone() {
	AnyType* ret = new AnyType;
	for (auto n : arrays) ret->arrays.push_back(n);
	ret->mArrayType = mArrayType;
	ret->mArraySize = mArraySize;
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

	// this code is a disaster
	if (no_brackets == false) {
		if (mArrayType == true) {
			if (mArraySize != 0)
				ss << "[" << mArraySize << "]";
			else 
				ss << "[]";
		} else if (arrays.size() > 0) {
			for (auto sz : arrays) {
				ss << "[" << sz << "]";
			}
		}
	} else {
		if (mArrayType == true) {
			if (mArraySize != 0)
				ss << "_" << mArraySize;
			else 
				ss << "_ARRAY";
		} else if (arrays.size() > 0) {
			for (auto sz : arrays) {
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
	}

	if (t->isArrayTy()) {
		ArrayType *at = (ArrayType *)t;
		ret = AnyType::Create(at->getElementType());
		ret->mArrayType = true; 
		ret->mArraySize = (int)at->getNumElements();
	}

	return ret;
}

bool AnyType::isSigned() {
	return (type[0] == 'i');
}

Type *AnyType::getType() {
	Type *initial = ::getType(type);

	for (int i = 0; i < numPointers; i++) {
		initial = initial->getPointerTo(0);
	}

	if (mArrayType && mArraySize) {
		initial = ArrayType::get(initial, mArraySize);
	} else if (mArrayType && mArraySize == 0) {
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

