//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <cstdlib>
#include <cctype>

#include "lex_helpers.h"
#include "lex.h"

using namespace orange::parser;

bool orange::parser::IsIntegerToken(const Token* tok) {
	return IsUIntToken(tok) || IsIntToken(tok);
}

bool orange::parser::IsUIntToken(const Token* tok) {
	return tok->type == VAL_UINT   || tok->type == VAL_UINT8  ||
	       tok->type == VAL_UINT16 || tok->type == VAL_UINT32 ||
	       tok->type == VAL_UINT64;
}

bool orange::parser::IsIntToken(const Token* tok) {
	return tok->type == VAL_INT   || tok->type == VAL_INT8  ||
	       tok->type == VAL_INT16 || tok->type == VAL_INT32 ||
	       tok->type == VAL_INT64;
}

bool orange::parser::IsFloatingPointToken(const Token* tok) {
	return tok->type == VAL_DOUBLE || tok->type == VAL_FLOAT;
}

int orange::parser::IntegerTokenBase(const Token* tok) {
	if (IsIntegerToken(tok) == false) return -1;

	// If we don't have at least 2 characters, we'll always be base 10.
	if (tok->value.length() < 2) return 10;

	if      (tok->value[1] == 'b') return 2;
	else if (tok->value[1] == 'o') return 8;
	else if (tok->value[1] == 'x') return 16;

	return 10;
}

int64_t orange::parser::ToInt(const Token* tok) {
	if (IsIntToken(tok) == false)
		throw std::runtime_error("Cannot convert non-int token to int.");

	std::string stripped_value = tok->value;
	int base = IntegerTokenBase(tok);

	// Strip away base indicator, if one exists.
	if (stripped_value.length() > 2 && isalpha(stripped_value[1]))
		stripped_value = stripped_value.substr(2);

	return strtoll(stripped_value.c_str(), nullptr, base);
}

uint64_t orange::parser::ToUInt(const Token* tok) {
	if (IsUIntToken(tok) == false)
		throw std::runtime_error("Cannot convert non-uint token to uint.");

	std::string stripped_value = tok->value;
	int base = IntegerTokenBase(tok);

	// Strip away base indicator, if one exists.
	if (stripped_value.length() > 2 && isalpha(stripped_value[1]))
		stripped_value = stripped_value.substr(2);

	return strtoull(stripped_value.c_str(), nullptr, base);
}

float orange::parser::ToFloat(const Token* tok) {
	if (tok->type != VAL_FLOAT)
		throw std::runtime_error("Cannot convert non-float token to float.");

	return strtof(tok->value.c_str(), nullptr);
}

double orange::parser::ToDouble(const Token* tok) {
	if (tok->type != VAL_DOUBLE)
		throw std::runtime_error("Cannot convert non-double token to double.");

	return strtod(tok->value.c_str(), nullptr);
}
