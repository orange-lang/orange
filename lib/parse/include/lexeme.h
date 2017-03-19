/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <string> 

#include "tokens.h"

namespace orange { namespace parse {
	struct Lexeme {
		std::string sourceFile;

		int lineNumber; 
		int columnNumber;

		Token token;

		std::string value;
	};
}}
