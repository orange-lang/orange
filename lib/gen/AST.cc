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
	} else if (typeStr == "void") {
		return Type::getVoidTy(getGlobalContext());
	} else {
		std::cerr << "FATAL: unknown type " << typeStr << "!\n";
	}

	return nullptr;
}

