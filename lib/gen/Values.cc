#include "gen/Values.h"
#include "gen/generator.h"

Value* UIntVal::Codegen() {
	return ConstantInt::get(getGlobalContext(), APInt(size, value));
}

Value* IntVal::Codegen() {
	return ConstantInt::get(getGlobalContext(), APInt(size, value));
}

StrVal::StrVal(std::string v) {
	value = v.substr(1, v.length()-2);
}

Value* StrVal::Codegen() {
	Value *v = CG::Builder.CreateGlobalString(value);
	return CG::Builder.CreateConstGEP2_32(v, 0, 0); 
}

BaseVal *ValFactory::produce() {
	BaseVal *ret = nullptr;

	if (size == "?") {
		std::string newSize = "";
		// read value until it's no longer a number or decimal.
		unsigned int ptr = 0;
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