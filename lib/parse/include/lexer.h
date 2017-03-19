/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>
#include <istream>

namespace orange { namespace parse {
	class Lexeme;

	class Lexer {
	private:
		std::istream& mInput;

        Lexeme lexNumber();
	public:
		Lexeme next();

		Lexer(std::istream& input);
	};
}}
