//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>

#include <libparse/parser.h>
#include <libast/type.h>
#include <libast/flag.h>
#include "lex_stream.h"
#include "lex_helpers.h"
#include "parser-private.h"

using namespace orange::ast;
using namespace orange::parser;
using namespace orange::parser::impl;

Identifier* impl::Parser::parse_identifier() {
	auto id = parse_identifier_base();
	if (id == nullptr) return nullptr;

	auto generics = parse_opt_generic_spec();
	if (generics == nullptr) throw std::runtime_error("Don't know how to use generics in IDs yet");

	return id;
}

Generics* impl::Parser::parse_opt_generic_spec() {
	if (mStream.peek()->type != LESS_THAN) return nullptr;
	throw std::runtime_error("Don't know how to parse generic IDs yet");
}

Identifier* impl::Parser::parse_identifier_base() {
	if (mStream.eof()) return nullptr;

	if (mStream.peek()->type == IDENTIFIER) {
		return CreateNode<NamedIDExpr>(mStream.get()->value);
	} else if (mStream.peek()->type == TILDE) {
		mStream.get();

		if (mStream.peek()->type != IDENTIFIER)
			throw std::runtime_error("Expected identifier");

		return CreateNode<DtorIDExpr>(CreateNode<NamedIDExpr>(mStream.get()->value));
	} else return nullptr;
}

Identifier* impl::Parser::parse_full_identifier() {
	Identifier* LHS = parse_identifier_base();
	if (LHS == nullptr) return nullptr;

	while (mStream.eof() == false) {
		bool done = false;

		Identifier* RHS = nullptr;

		switch (mStream.peek()->type) {
			case TokenType::DOT:
				mStream.get();
				RHS = parse_identifier_base();
				if (RHS == nullptr) throw std::runtime_error("Expected identifier");
				LHS = CreateNode<AccessIDExpr>(LHS, RHS);
				break;
			case TokenType::LESS_THAN:
				throw std::runtime_error("Don't know how to handle generics in full IDs");
				break;
			default:
				done = true;
				break;
		}

		if (done) break;
	}

	return LHS;
}
