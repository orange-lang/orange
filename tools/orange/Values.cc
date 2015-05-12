/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/Values.h>
#include <orange/generator.h>
#include <algorithm>

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    std::string::size_type start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

StrElement operator+(const char *s, StrElement& element) {
	return StrElement(s + element.m_str);
}

StrElement operator+(StrElement element, const char* s) {
	std::string cpp_s = element;
	cpp_s += s;
	return StrElement(cpp_s);
}

std::ostream& operator<< (std::ostream& stream, const StrElement& element) {
	return stream << element.m_str;
}

StrVal::StrVal(StrElement value) : m_value(value) {
	std::string cpp_s = m_value;
	cpp_s = cpp_s.substr(1, cpp_s.length()-2);
	replaceAll(cpp_s, "\\n", "\n");
	m_value = cpp_s;
}

Value* StrVal::Codegen() {
	Value *v = GE::builder()->CreateGlobalString((std::string)m_value);
	return GE::builder()->CreateConstGEP2_32(v, 0, 0); 
}

Value* UIntVal::Codegen() {
	return ConstantInt::get(GE::runner()->context(), APInt(size, value));
}

Value* IntVal::Codegen() {
	return ConstantInt::get(GE::runner()->context(), APInt(size, value));
}

Value* FloatVal::Codegen() {
	return ConstantFP::get(getLLVMType(), value);
}

Value* DoubleVal::Codegen() {
	return ConstantFP::get(getLLVMType(), value);
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

		size = newSize;
	}

	// handle characters 
	if (value.length() == 3 && value[0] == '\'' && value[2] == '\'') {
		if (size == "u") {
			ret = new UIntVal(value[1], 64);
		} else if (size == "i" || size == "") {
			ret = new IntVal(value[1], 64);
		} else if (size == "i8") {
			ret = new IntVal((int8_t)value[1], 8);
		} else if (size == "u8") {
			ret = new UIntVal((uint8_t)value[1], 8);
		} else if (size == "i16") {
			ret = new IntVal((int16_t)value[1], 16);
		} else if (size == "u16") {
			ret = new UIntVal((uint16_t)value[1], 16);
		} else if (size == "i32") {
			ret = new IntVal((int32_t)value[1], 32);
		} else if (size == "u32") {
			ret = new UIntVal((uint32_t)value[1], 32);
		} else if (size == "i64") {
			ret = new IntVal((int32_t)value[1], 32);
		} else if (size == "u64") {
			ret = new UIntVal((uint64_t)value[1], 64);
		}  

		return ret;
	}

	if (size == "u") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal(v, 64);
	} else if (size == "i" || size == "") {
		int64_t v = std::stoll(value);
		ret = new IntVal(v, 64);
	} else if (size == "i8") {
		int64_t v = std::stoll(value);
		ret = new IntVal((int8_t)v, 8);
	} else if (size == "u8") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint8_t)v, 8);
	} else if (size == "i16") {
		int64_t v = std::stoll(value);
		ret = new IntVal((int16_t)v, 16);
	} else if (size == "u16") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint16_t)v, 16);
	} else if (size == "i32") {
		int64_t v = std::stoll(value);
		ret = new IntVal((int32_t)v, 32);
	} else if (size == "u32") {
		uint64_t v = std::stoull(value);
		ret = new UIntVal((uint32_t)v, 32);
	} else if (size == "i64") {
		int64_t v = std::stoll(value);
		ret = new IntVal((int32_t)v, 32);
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