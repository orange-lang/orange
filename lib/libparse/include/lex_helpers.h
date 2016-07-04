//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <cstdint>

#include <libast/type.h>

namespace orange { namespace parser {
	class Token;

	/// Returns whether or not a token represents an integer value
	bool IsIntegerToken(const Token* tok);

	/// Returns whether or not a token represents a uint value
	bool IsUIntToken(const Token* tok);

	/// Returns whether or not a token represents a int value
	bool IsIntToken(const Token* tok);

	/// Returns whether or not a token represents a floating point value
	bool IsFloatingPointToken(const Token* tok);

	/// Gets the base of a integer token (UINT or INT)
	int IntegerTokenBase(const Token* tok);

	/// Converts a INTn token to int64_t
	int64_t ToInt(const Token* tok);

	/// Converts a UINTn token to uint64_t
	uint64_t ToUInt(const Token* tok);

	/// Converts a FLOAT token to float
	float ToFloat(const Token* tok);

	/// Converts a DOUBLE token to double
	double ToDouble(const Token* tok);

	orange::ast::Type* TypeFromToken(const Token* tok);
}}

