/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <cctype>
#include <sstream>
#include <iostream>

#include "lexer.h"
#include "lexeme.h"
#include "numberLexer.h"

using namespace orange::parse;

Lexer::Lexer(std::istream& input) : mInput(input) { }

Lexeme Lexer::next() {
    // Consume all whitespace
    while (std::isspace(mInput.peek())) mInput.get();

    if (std::isdigit(mInput.peek())) {
        return lexNumber(mInput);
    }

	return Lexeme();
}


