//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <map>

#include <libparse/parser.h>
#include <libast/type.h>
#include <libast/flag.h>
#include <libast/typecheck.h>
#include "lex_stream.h"
#include "lex_helpers.h"

namespace orange { namespace parser { namespace impl {
	using namespace orange::ast;

	int GetOperatorPrecedence(TokenType tok);

	enum OperatorAssociativity { LEFT, RIGHT };
	OperatorAssociativity GetAssociativity(TokenType tok);

	UnaryOp GetUnaryOp(TokenType ty);
	BinOp GetBinOp(TokenType ty);
}}}
