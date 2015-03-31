#include "gen/AST.h"
#include "gen/generator.h"
typedef CodeGenerator CG;


Type *getType(std::string typeStr) {
	if (typeStr == "int" || typeStr == "int64") {
		return Type::getInt64Ty(getGlobalContext());
	} else if (typeStr == "int8") {
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


ArgExpr::ArgExpr(std::string* type, std::string* name) {
	this->type = type ? *type : "";
	this->name = name ? *name : "";
	
	// if it's not u, then it's signed
	if (this->type != "" && (this->type)[0] == 'u') {
		isSigned = false;
	} else isSigned = true;

	CG::Symtab->create(this->name);
	if (this->type != "") {
		CG::Symtab->objs[this->name]->setType(getType(this->type));
	}
	CG::Symtab->objs[this->name]->isSigned = isSigned;
}

FunctionStatement::FunctionStatement(std::string* name, ArgList *args, Block *body) {
	this->name = name ? *name : "";
	this->args = args;
	this->body = body;
}

BinOpExpr::BinOpExpr(Expression *LHS, char op, Expression *RHS) {
	this->LHS = LHS;
	this->op = op;
	this->RHS = RHS;
}

BaseVal *ValFactory::produce() {
	BaseVal *ret = nullptr;

	if (size == "?") {
		std::string newSize = "";
		// read value until it's no longer a number or decimal.
		int ptr = 0;
		for (; ptr < value.length(); ptr++) {
			if (value[ptr] != '.' && isdigit(value[ptr]) == false)
				continue;
			newSize += value[ptr];
		}

		printf("Determined size: \"%s\"\n", newSize.c_str());
		size = newSize;
	}

	if (size == "u") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal(v, 64);
	} else if (size == "i" || size == "") {
		int64_t v = std::stoll(value);
		ret = new IntVal(v, 64);
	} else if (size == "i8") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int8_t)v, 8);
	} else if (size == "u8") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint8_t)v, 8);
	} else if (size == "i16") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int16_t)v, 16);
	} else if (size == "u16") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint16_t)v, 16);
	} else if (size == "i32") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int32_t)v, 32);
	} else if (size == "u32") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint32_t)v, 32);
	} else if (size == "i64") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int32_t)v, 32);
	} else if (size == "u64") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint64_t)v, 64);
	} else if (size == "f") {
		float v = std::stof(value);
		ret = new FloatVal(v);
	} else if (size == "d") {
		double v = std::stod(value);
		ret = new DoubleVal(v);
	} else if (size == "x") {
		// base 16
		uint64_t v = std::stoull(value, nullptr, 16);
		ret = new UIntVal(v, 64);
	} else if (size == "b") {
		// base 2
		uint64_t v = std::stoull(value, nullptr, 2);
		ret = new UIntVal(v, 64);
	}

	return ret;
}
