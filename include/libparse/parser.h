//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <istream>
#include <libast/ast.h>

namespace orange { namespace parser {
	class Parser {
	private:
		std::istream& mStream;
	public:
		/// Parse the stream and return an AST.
		ast::LongBlockExpr* parse();

		/// Construct the parser, using a stream.
		Parser(std::istream& stream);
	};
}}