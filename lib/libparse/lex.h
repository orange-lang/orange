//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <string>

namespace orange { namespace parser {
	enum TokenType {
	};

	class Token {
	public:
		TokenType type;
		std::string value;

		Token() { }
		Token(TokenType ty, std::string v) : type(ty), value(v) { }
	};

	class Lexer {
	private:
		std::istream& mStream;
	public:
		/// Reads the next token from the stream.
		/// Returns nullptr on EOF. Throws exception on error.
		Token* readToken();

		/// Returns whether or not we're at the end of the stream.
		bool eof() const;

		Lexer(std::istream& stream);
	};
}}
