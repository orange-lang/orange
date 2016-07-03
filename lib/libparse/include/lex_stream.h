//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <vector>
#include "lex.h"

namespace orange { namespace parser {
	/// A stream of tokens from the lexer. Allows for n-lookahead, n-consumption,
	/// and n-putback.
	class LexStream {
	private:
		std::vector<Token*> mBuffer;
		std::vector<Token*> mConsumed;
		Lexer mLexer;
	public:
		/// Peeks at the next token in the stream.
		Token* peek();

		/// Gets the next token from the stream.
		Token* get();

		/// Peeks at the next n tokens from the stream.
		std::vector<Token*> peek(int n);

		/// Gets the next n tokens from the strema.
		std::vector<Token*> get(int n);

		/// Tells the current position of the lexer stream.
		unsigned long tell();

		/// Sets the current position of the lexer stream, offset from the beginning
		void seek(unsigned long pos);

		/// Gets whether or not the stream is at EOF.
		bool eof() const;

		LexStream(std::istream& stream);
	};
}}