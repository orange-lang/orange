#include "gen/AST.h"
#include "gen/generator.h"
typedef CodeGenerator CG;


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

