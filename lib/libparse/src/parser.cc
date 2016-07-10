//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libparse/parser.h>
#include "parser-private.h"

using namespace orange::ast;
using namespace orange::parser;

namespace orange { namespace parser { namespace impl {
	using namespace orange::ast;

	class Parser {
	private:
		std::istream& mStream;
	public:
		LongBlockExpr* parse() { return new LongBlockExpr(); }

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

LongBlockExpr* Parser::parse() {
	return mParserImpl->parse();
}

Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) {

}
