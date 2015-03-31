#include "gen/AST.h"
#include "gen/generator.h"
typedef CodeGenerator CG;

bool returnsPtr(std::string className) {
	return className == "VarExpr" || className == "IfStatement" || className == "DerefId" || className == "VarDeclExpr";
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

	return initial;
}

