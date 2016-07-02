//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libparse/parser.h>
#include "lex_stream.h"

namespace orange { namespace parser { namespace impl {
	class Parser {
	private:
		LexStream mStream;
	public:
		/* TODO: add parsing functions */

		ast::LongBlockExpr* parse();

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

using namespace orange::parser;

orange::ast::LongBlockExpr* Parser::parse() { return mParserImpl->parse(); }
Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) { }


