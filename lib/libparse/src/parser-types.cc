//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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
#include "parser-private.h"

using namespace orange::ast;
using namespace orange::parser;
using namespace orange::parser::impl;

Type* impl::Parser::parse_type() {
	return parse_complex_type();
}

Type* impl::Parser::parse_basic_type() {
	if      (mStream.eof())                  return nullptr;
	else if (mStream.peek()->type == INT)    return new BuiltinType(BuiltinTypeKind::INT);
	else if (mStream.peek()->type == INT8)   return new BuiltinType(BuiltinTypeKind::INT8);
	else if (mStream.peek()->type == INT16)  return new BuiltinType(BuiltinTypeKind::INT16);
	else if (mStream.peek()->type == INT32)  return new BuiltinType(BuiltinTypeKind::INT32);
	else if (mStream.peek()->type == INT64)  return new BuiltinType(BuiltinTypeKind::INT64);
	else if (mStream.peek()->type == UINT)   return new BuiltinType(BuiltinTypeKind::UINT);
	else if (mStream.peek()->type == UINT8)  return new BuiltinType(BuiltinTypeKind::UINT8);
	else if (mStream.peek()->type == UINT16) return new BuiltinType(BuiltinTypeKind::UINT16);
	else if (mStream.peek()->type == UINT32) return new BuiltinType(BuiltinTypeKind::UINT32);
	else if (mStream.peek()->type == UINT64) return new BuiltinType(BuiltinTypeKind::UINT64);
	else if (mStream.peek()->type == FLOAT)  return new BuiltinType(BuiltinTypeKind::FLOAT);
	else if (mStream.peek()->type == DOUBLE) return new BuiltinType(BuiltinTypeKind::DOUBLE);
	else if (mStream.peek()->type == VAR)    return new BuiltinType(BuiltinTypeKind::VAR);
	else if (mStream.peek()->type == VOID)   return new BuiltinType(BuiltinTypeKind::VOID);
	else if (mStream.peek()->type == CHAR)   return new BuiltinType(BuiltinTypeKind::CHAR);

	return nullptr;
}

Type* impl::Parser::parse_complex_type() {
	Type* LHS = parse_complex_type_base();
	if (LHS == nullptr) return nullptr;

	while (!mStream.eof()) {
		bool done = false;

		Expression* expr;
		Type* RHS;

		switch (mStream.peek()->type) {
			case TokenType::OPEN_BRACKET:
				mStream.get();
				expr = parse_expression();
				if (expr == nullptr) throw std::runtime_error("Expected expression");

				LHS = new ArrayType(LHS, expr);

				if (mStream.get()->type != CLOSE_BRACKET)
					throw std::runtime_error("Expected ]");

				break;
			case TokenType::TIMES:
				mStream.get();
				LHS = new PointerType(LHS);
				break;
			case TokenType::BIT_AND:
				mStream.get();
				LHS = new ReferenceType(LHS);
				break;
			case TokenType::LESS_THAN:
				throw std::runtime_error("Can't handle generic types yet");
			case TokenType::DOT:
				mStream.get();
				RHS = parse_base_id_type();
				if (RHS == nullptr) throw std::runtime_error("Expected type");

				LHS = new AccessType(LHS, RHS);
				break;
			default: done = true;
		}

		if (done) break;
	}

	return LHS;
}

Type* impl::Parser::parse_complex_type_base() {
	Type* ty = nullptr;

	if ((ty = parse_basic_type()) != nullptr) return ty;
	if ((ty = parse_tuple_or_func_type()) != nullptr) return ty;
	if ((ty = parse_base_id_type()) != nullptr) return ty;

	return nullptr;
}

Type* impl::Parser::parse_tuple_or_func_type() {
	if (mStream.peek()->type != OPEN_PAREN) return nullptr;
	mStream.get();

	std::vector<Type*> types;

	Type* ty = parse_type();
	if (ty == nullptr) throw std::runtime_error("Expected type");
	types.push_back(ty);

	bool trailingComma = false;

	while (!mStream.eof()) {
		if (mStream.peek()->type == CLOSE_PAREN) break;
		if (mStream.peek()->type == COMMA) {
			mStream.get();

			// We allow trailing commas here
			if (mStream.peek()->type == CLOSE_PAREN) {
				trailingComma = true;
				break;
			}

			ty = parse_type();
			if (ty == nullptr) throw std::runtime_error("Expected type");
			types.push_back(ty);
		}
	}

	if (mStream.peek()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	if (trailingComma == false && mStream.peek()->type == ARROW) {
		mStream.get();

		auto returnTy = parse_type();
		if (returnTy == nullptr) throw std::runtime_error("Expected return type");

		return new FunctionType(types, returnTy);
	} else {
		return new TupleType(types);
	}
}

Type* impl::Parser::parse_base_id_type() {
	if (mStream.peek()->type == IDENTIFIER) {
		return new IdentifierType(CreateNode<NamedIDExpr>(mStream.peek()->value));
	}

	Type* ty = nullptr;

	if ((ty = parse_operator_id_ty()) != nullptr) return ty;

	return nullptr;
}

Type* impl::Parser::parse_operator_id_ty() {
	if (mStream.peek()->type != OPERATOR) return nullptr;
	throw std::runtime_error("Don't know how to parse operators yet");
}


