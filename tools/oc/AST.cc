#include "AST.h"

ArgExpr::ArgExpr(std::string* type, std::string* name) {
	this->type = type ? *type : "";
	this->name = name ? *name : "";

	// printf("[Creating arg %s (type: %s)...] ", this->name.c_str(), this->type.c_str());
}

FunctionStatement::FunctionStatement(std::string* name, ArgList *args, Block *body) {
	this->name = name ? *name : "";
	this->args = args;
	this->body = body;
	

	// printf("[Creating function %s...] ", this->name.c_str());
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
		std::cout << v << " ";
	} else if (size == "i" || size == "") {
		int64_t v = std::stoll(value);
		ret = new IntVal(v, 64);
		std::cout << v << " ";
	} else if (size == "i8") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int8_t)v, 8);
		std::cout << v << " ";
	} else if (size == "u8") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint8_t)v, 8);
		std::cout << v << " ";
	} else if (size == "i16") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int16_t)v, 16);
		std::cout << v << " ";
	} else if (size == "u16") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint16_t)v, 16);
		std::cout << v << " ";
	} else if (size == "i32") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int32_t)v, 32);
		std::cout << v << " ";
	} else if (size == "u32") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint32_t)v, 32);
		std::cout << v << " ";
	} else if (size == "i64") {
		int64_t v = std::stoll(value);
		ret = new UIntVal((int32_t)v, 32);
		std::cout << v << " ";
	} else if (size == "u64") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint64_t)v, 64);
		std::cout << v << " ";
	} else if (size == "f") {
		float v = std::stof(value);
		ret = new FloatVal(v);
		std::cout << v << " ";
	} else if (size == "d") {
		double v = std::stod(value);
		ret = new DoubleVal(v);
		std::cout << v << " ";
	} else if (size == "x") {
		// base 16
		uint64_t v = std::stoull(value, nullptr, 16);
		ret = new UIntVal(v, 64);
		std::cout << v << " ";
	} else if (size == "b") {
		// base 2
		uint64_t v = std::stoull(value, nullptr, 2);
		ret = new UIntVal(v, 64);
		std::cout << v << " ";
	}

	return ret;
}
