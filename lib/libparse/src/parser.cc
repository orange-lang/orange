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
using namespace orange::ast;
using namespace orange::parser;
using namespace orange::parser::impl;

int impl::GetOperatorPrecedence(TokenType tok) {
	const static std::map<TokenType, int> OperatorPrecedence = {
		{TokenType::PLUS, 4}, {TokenType::MINUS, 4},
		{TokenType::SHIFT_LEFT, 5}, {TokenType::SHIFT_RIGHT, 5},
		{TokenType::LESS_THAN, 6}, {TokenType::GREATER_THAN, 6},
		{TokenType::LEQ, 6}, {TokenType::GEQ, 6},
		{TokenType::EQUALS, 7}, {TokenType::NEQ, 7},
		{TokenType::BIT_AND, 8},
		{TokenType::BIT_XOR, 9},
		{TokenType::BIT_OR, 10},
		{TokenType::AND, 11},
		{TokenType::OR, 12},
		{TokenType::QUESTION, 13}, {TokenType::ASSIGN, 13},
		{TokenType::PLUS_ASSIGN, 13}, {TokenType::MINUS_ASSIGN, 13},
		{TokenType::TIMES_ASSIGN, 13}, {TokenType::DIVIDE_ASSIGN, 13},
		{TokenType::REMAINDER_ASSIGN, 13}, {TokenType::SHIFT_LEFT_ASSIGN, 13},
		{TokenType::SHIFT_RIGHT_ASSIGN, 13}, {TokenType::BIT_OR_ASSIGN, 13},
		{TokenType::BIT_AND_ASSIGN, 13}, {TokenType::BIT_XOR_ASSIGN, 13}
	};

	auto it = OperatorPrecedence.find(tok);
	if (it == OperatorPrecedence.end()) return -1;
	return it->second;
}

OperatorAssociativity impl::GetAssociativity(TokenType tok) {
	auto prec = GetOperatorPrecedence(tok);

	if (prec == 13) return OperatorAssociativity::RIGHT;
	else return OperatorAssociativity::LEFT;
}

UnaryOp impl::GetUnaryOp(TokenType ty) {
	switch (ty) {
		case TokenType::INCREMENT: return UnaryOp::INCREMENT;
		case TokenType::DECREMENT: return UnaryOp::DECREMENT;
		case TokenType::MINUS:     return UnaryOp::MINUS;
		case TokenType::NOT:       return UnaryOp::NOT;
		case TokenType::TILDE:     return UnaryOp::TILDE;
		case TokenType::TIMES:     return UnaryOp::TIMES;
		case TokenType::BIT_AND:   return UnaryOp::REFERENCE;
		default:
			throw std::runtime_error("Not a valid unary operator token");
	}
}

BinOp impl::GetBinOp(TokenType ty) {
	switch (ty) {
		case TokenType::PLUS:               return BinOp::ADD;
		case TokenType::MINUS:              return BinOp::SUBTRACT;
		case TokenType::DIVIDE:             return BinOp::DIVIDE;
		case TokenType::TIMES:              return BinOp::MULTIPLY;
		case TokenType::REMAINDER:          return BinOp::REMAINDER;
		case TokenType::BIT_OR:             return BinOp::BIT_OR;
		case TokenType::BIT_AND:            return BinOp::BIT_AND;
		case TokenType::BIT_XOR:            return BinOp::BIT_XOR;
		case TokenType::SHIFT_LEFT:         return BinOp::SHIFT_LEFT;
		case TokenType::SHIFT_RIGHT:        return BinOp::SHIFT_RIGHT;
		case TokenType::ASSIGN:             return BinOp::ASSIGN;
		case TokenType::EQUALS:             return BinOp::EQUALS;
		case TokenType::PLUS_ASSIGN:        return BinOp::PLUS_ASSIGN;
		case TokenType::MINUS_ASSIGN:       return BinOp::MINUS_ASSIGN;
		case TokenType::TIMES_ASSIGN:       return BinOp::TIMES_ASSIGN;
		case TokenType::DIVIDE_ASSIGN:      return BinOp::DIVIDE_ASSIGN;
		case TokenType::REMAINDER_ASSIGN:   return BinOp::REMAINDER_ASSIGN;
		case TokenType::SHIFT_LEFT_ASSIGN:  return BinOp::SHIFT_LEFT_ASSIGN;
		case TokenType::SHIFT_RIGHT_ASSIGN: return BinOp::SHIFT_RIGHT_ASSIGN;
		case TokenType::BIT_OR_ASSIGN:      return BinOp::BIT_OR_ASSIGN;
		case TokenType::BIT_AND_ASSIGN:     return BinOp::BIT_AND_ASSIGN;
		case TokenType::BIT_XOR_ASSIGN:     return BinOp::BIT_XOR_ASSIGN;
		case TokenType::LESS_THAN:          return BinOp::LESS_THAN;
		case TokenType::GREATER_THAN:       return BinOp::GREATER_THAN;
		case TokenType::LEQ:                return BinOp::LEQ;
		case TokenType::GEQ:                return BinOp::GEQ;
		case TokenType::NEQ:                return BinOp::NEQ;
		case TokenType::AND:                return BinOp::AND;
		case TokenType::OR:                 return BinOp::OR;
		default:
			throw std::runtime_error("Not a valid binary operator token");
	}
}

bool impl::Parser::isTerm(Token* tok) {
	return tok->type == NEWLINE || tok->type == SEMICOLON;
}

bool impl::Parser::checkNext(TokenType ty) {
	return mStream.peek() != nullptr && mStream.peek()->type == ty;
}

std::vector<Node *> impl::Parser::parse_opt_statements() {
	return parse_statements(true);
}

std::vector<Node *> impl::Parser::parse_statements(bool allow_eps) {
	std::vector<Node *> statements;

	if (mStream.peek() && isTerm(mStream.peek())) {
		mStream.get();
		return parse_statements();
	}

	if (mStream.peek() && mStream.peek()->type == COMMENT) {
		statements.push_back(CreateNode<CommentStmt>(mStream.get()->value));

		auto remaining = parse_statements();
		statements.insert(statements.end(), remaining.begin(), remaining.end());

		return statements;
	} else {
		auto stmt = parse_statement();

		if (stmt == nullptr) {
			if (allow_eps) return statements;
			throw std::runtime_error("Expected statement");
		}

		statements.push_back(stmt);

		if (mStream.peek() && isTerm(mStream.peek())) {
			parse_term();

			auto remaining = parse_statements();
			statements.insert(statements.end(), remaining.begin(), remaining.end());
		}

		return statements;
	}
}

Token* impl::Parser::parse_term() {
	if (!isTerm(mStream.peek())) return nullptr;
	return mStream.get();
}

LongBlockExpr* impl::Parser::parse_long_block() {
	if (checkNext(OPEN_CURLY) == false) return nullptr;
	mStream.get();

	auto stmts = parse_opt_statements();

	if (checkNext(CLOSE_CURLY) == false) throw std::runtime_error("Expected }");

	return CreateNode<LongBlockExpr>(stmts);
}

ShortBlockExpr* impl::Parser::parse_short_block() {
	if (checkNext(COLON) == false) return nullptr;

	auto stmt = parse_statement();
	if (stmt == nullptr) throw std::runtime_error("Expected statement");

	return CreateNode<ShortBlockExpr>(stmt);
}

BlockExpr* impl::Parser::parse_block() {
	BlockExpr* block = nullptr;

	if ((block = parse_long_block()) != nullptr) return block;
	if ((block = parse_short_block()) != nullptr) return block;

	throw std::runtime_error("Expected block");
}

/*
 * Types
 */

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

/*
 * Identifier
 */

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

/*
 * Statements
 */

Node* impl::Parser::parse_statement() {
	Node* stmt = nullptr;

	if ((stmt = parse_var_decl()) != nullptr) return stmt;
	if ((stmt = parse_class()) != nullptr) return stmt;
	if ((stmt = parse_partial_class()) != nullptr) return stmt;
	if ((stmt = parse_long_block()) != nullptr) return stmt;
	if ((stmt = parse_break_stmt()) != nullptr) return stmt;
	if ((stmt = parse_continue_stmt()) != nullptr) return stmt;
	if ((stmt = parse_yield_stmt()) != nullptr) return stmt;
	if ((stmt = parse_function()) != nullptr) return stmt;
	if ((stmt = parse_aggregate()) != nullptr) return stmt;
	if ((stmt = parse_extern_fn()) != nullptr) return stmt;
	if ((stmt = parse_interface()) != nullptr) return stmt;
	if ((stmt = parse_namespace()) != nullptr) return stmt;
	if ((stmt = parse_import()) != nullptr) return stmt;
	if ((stmt = parse_extension()) != nullptr) return stmt;
	if ((stmt = parse_getter()) != nullptr) return stmt;
	if ((stmt = parse_setter()) != nullptr) return stmt;
	if ((stmt = parse_property()) != nullptr) return stmt;
	if ((stmt = parse_enum()) != nullptr) return stmt;
	if ((stmt = parse_expr_statement()) != nullptr) return stmt;
	if ((stmt = parse_delete()) != nullptr) return stmt;
	if ((stmt = parse_for_loop()) != nullptr) return stmt;
	if ((stmt = parse_foreach()) != nullptr) return stmt;
	if ((stmt = parse_while()) != nullptr) return stmt;
	if ((stmt = parse_forever()) != nullptr) return stmt;
	if ((stmt = parse_do_while()) != nullptr) return stmt;
	if ((stmt = parse_throw_stmt()) != nullptr) return stmt;

	return nullptr;
}

VarDeclExpr* impl::Parser::parse_var_decl() {
	if (mStream.eof()) return nullptr;

	auto pos = mStream.tell();
	auto constFlag = parse_opt_const();

	if (mStream.get()->type != VAR) {
		mStream.seek(pos);
		return nullptr;
	}

	auto ids = parse_identifiers();
	auto tys = parse_opt_type_spec_list();
	auto expr = parse_opt_value();

	auto node = CreateNode<VarDeclExpr>(ids, tys, expr);
	if (constFlag != nullptr) node->flags.push_back(constFlag);

	return node;
}

Flag* impl::Parser::parse_opt_const() {
	if (mStream.peek()->type != CONST) return nullptr;
	return new ConstFlag();
}

std::vector<Identifier*> impl::Parser::parse_identifiers() {
	std::vector<Identifier*> ids;
	if (mStream.eof()) return ids;

	if (mStream.peek()->type == OPEN_PAREN) {
		mStream.get();

		auto remaining = parse_identifier_list();
		ids.insert(ids.end(), remaining.begin(), remaining.end());

		if (ids.size() == 0) throw std::runtime_error("Expected identifier inside parenthesis");

		if (mStream.get()->type != CLOSE_PAREN) throw std::runtime_error("Expected )");
	} else {
		auto id = parse_identifier();
		if (id == nullptr) throw std::runtime_error("Expected identifier");

		ids.push_back(id);
	}

	return ids;
}

std::vector<Identifier*> impl::Parser::parse_identifier_list() {
	std::vector<Identifier*> ids;

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");
	ids.push_back(id);

	while (mStream.peek()->type == COMMA) {
		auto id = parse_identifier();
		if (id == nullptr) throw std::runtime_error("Expected identifier");
		ids.push_back(id);
	}

	return ids;
}

std::vector<Type*> impl::Parser::parse_opt_type_spec_list() {
	std::vector<Type*> tys;
	if (mStream.peek()->type != COLON) return tys;
	mStream.get();

	auto ty = parse_type();
	if (ty == nullptr) throw std::runtime_error("Expected type");
	tys.push_back(ty);

	while (mStream.peek()->type == COMMA) {
		auto ty = parse_type();
		if (ty == nullptr) throw std::runtime_error("Expected type");
		tys.push_back(ty);
	}

	return tys;
}

Expression* impl::Parser::parse_opt_value() {
	if (mStream.peek()->type != ASSIGN) return nullptr;
	mStream.get();
	return parse_expression();
}

EnumStmt* impl::Parser::parse_enum() {
	auto pos = mStream.tell();
	auto flags = parse_flags();
	auto enumStmt = parse_enum_base();

	if (enumStmt == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	enumStmt->flags.insert(enumStmt->flags.end(), flags.begin(), flags.end());
	return enumStmt;
}

EnumStmt* impl::Parser::parse_enum_base() {
	if (mStream.peek()->type != ENUM) return nullptr;
	mStream.get();

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	if (mStream.get()->type != OPEN_CURLY)
		throw std::runtime_error("Expected {");

	auto values = parse_enum_values();

	if (mStream.get()->type != CLOSE_CURLY)
		throw std::runtime_error("Expected }");

	return CreateNode<EnumStmt>(id, values);
}

std::vector<EnumValue*> impl::Parser::parse_enum_values() {
	std::vector<EnumValue*> values;

	auto value = parse_enum_value();
	if (value == nullptr) return values;
	values.push_back(value);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto value = parse_enum_value();
		if (value == nullptr) throw std::runtime_error("Expected enumeration value");
		values.push_back(value);
	}

	return values;
}

EnumValue* impl::Parser::parse_enum_value() {
	if (mStream.peek()->type != IDENTIFIER) return nullptr;

	auto name = mStream.get()->value;
	std::vector<VarDeclExpr*> params = parse_opt_enum_params();

	return CreateNode<EnumValue>(CreateNode<NamedIDExpr>(name), params);
}

std::vector<VarDeclExpr*> impl::Parser::parse_opt_enum_params() {
	std::vector<VarDeclExpr*> params;
	if (mStream.peek()->type != OPEN_PAREN) return params;
	mStream.get();

	params = parse_param_list();

	if (mStream.get()->type == CLOSE_PAREN) throw std::runtime_error("Expected )");
	return params;
}


ClassStmt* impl::Parser::parse_class() {
	auto pos = mStream.tell();
	auto flags = parse_flags();
	auto classStmt = parse_base_class();

	if (classStmt == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	classStmt->flags.insert(classStmt->flags.end(), flags.begin(), flags.end());
	return classStmt;
}

ClassStmt* impl::Parser::parse_base_class() {
	if (mStream.peek()->type != CLASS) return nullptr;
	mStream.get();

	if (mStream.peek()->type != IDENTIFIER)
		throw std::runtime_error("Expected identifier");

	auto name = CreateNode<NamedIDExpr>(mStream.get()->value);
	auto supers = parse_opt_supers();
	auto body = parse_class_body();

	return CreateNode<ClassStmt>(name, supers, body);
}

std::vector<Identifier*> impl::Parser::parse_opt_supers() {
	std::vector<Identifier*> ids;
	if (mStream.peek()->type != COLON) return ids;

	auto id = parse_full_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");
	ids.push_back(id);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto id = parse_full_identifier();
		if (id == nullptr) throw std::runtime_error("Expected identifier");
		ids.push_back(id);
	}

	return ids;
}

ClassStmt* impl::Parser::parse_partial_class() {
	auto pos = mStream.tell();
	auto flags = parse_flags();

	if (mStream.peek()->type != PARTIAL) {
		mStream.seek(pos);
		return nullptr;
	}

	auto classStmt = parse_base_class();

	if (classStmt == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	classStmt->flags.insert(classStmt->flags.end(), flags.begin(), flags.end());
	classStmt->flags.push_back(new PartialFlag);
	return classStmt;
}

LongBlockExpr* impl::Parser::parse_class_body() {
	if (mStream.peek()->type != OPEN_CURLY)
		throw std::runtime_error("Expected {");

	auto stmts = parse_class_stmts();

	if (mStream.peek()->type != CLOSE_CURLY)
		throw std::runtime_error("Expected }");

	return CreateNode<LongBlockExpr>(stmts);
}

std::vector<Node*> impl::Parser::parse_class_stmts() {
	std::vector<Node *> statements;

	if (mStream.peek() && isTerm(mStream.peek())) {
		mStream.get();
		return parse_class_stmts();
	}

	if (mStream.peek() && mStream.peek()->type == COMMENT) {
		statements.push_back(CreateNode<CommentStmt>(mStream.get()->value));

		auto remaining = parse_class_stmts();
		statements.insert(statements.end(), remaining.begin(), remaining.end());

		return statements;
	} else {
		auto stmt = parse_class_stmt();

		if (stmt == nullptr) { return statements; }

		statements.push_back(stmt);

		if (mStream.peek() && isTerm(mStream.peek())) {
			parse_term();

			auto remaining = parse_class_stmts();
			statements.insert(statements.end(), remaining.begin(), remaining.end());
		}

		return statements;
	}
}

Node* impl::Parser::parse_class_stmt() {
	Node* node = nullptr;

	if ((node = parse_implicit_var()) != nullptr) return node;
	if ((node = parse_class()) != nullptr) return node;
	if ((node = parse_partial_class()) != nullptr) return node;
	if ((node = parse_function()) != nullptr) return node;
	if ((node = parse_aggregate()) != nullptr) return node;
	if ((node = parse_extern_fn()) != nullptr) return node;
	if ((node = parse_import()) != nullptr) return node;
	if ((node = parse_extension()) != nullptr) return node;
	if ((node = parse_property()) != nullptr) return node;
	if ((node = parse_enum()) != nullptr) return node;

	return nullptr;
}

FunctionExpr* impl::Parser::parse_function() {
	auto pos = mStream.tell();
	auto flags = parse_flags();
	auto functionExpr = parse_base_function();

	if (functionExpr == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	functionExpr->flags.insert(functionExpr->flags.end(), flags.begin(), flags.end());
	return functionExpr;
}

FunctionExpr* impl::Parser::parse_base_function() {
	if (mStream.peek()->type != DEF) return nullptr;
	mStream.get();

	auto id = parse_identifier();
	auto generics = parse_generics();

	if (mStream.peek()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto params = parse_param_list();

	if (mStream.peek()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto retType = parse_opt_func_type();
	auto body = parse_block();

	return CreateNode<FunctionExpr>(id, generics, params, retType, body);
}

std::vector<VarDeclExpr*> impl::Parser::parse_param_list() {
	std::vector<VarDeclExpr*> params;

	auto param = parse_implicit_var();
	if (param == nullptr) return params;
	params.push_back(param);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto param = parse_implicit_var();
		if (param == nullptr) return params;
		params.push_back(param);
	}

	return params;
}

Type* impl::Parser::parse_opt_func_type() {
	if (mStream.peek()->type != ARROW) return nullptr;
	mStream.get();

	return parse_type();
}

ExternFuncStmt* impl::Parser::parse_extern_fn() {
	auto pos = mStream.tell();
	auto flags = parse_flags();
	auto functionExpr = parse_base_extern();

	if (functionExpr == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	functionExpr->flags.insert(functionExpr->flags.end(), flags.begin(), flags.end());
	return functionExpr;
}

ExternFuncStmt* impl::Parser::parse_base_extern() {
	if (mStream.peek()->type != EXTERN) return nullptr;
	mStream.get();

	if (mStream.get()->type != DEF)
		throw std::runtime_error("Expecting def");

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expecting identifier");

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expecting (");

	auto params = parse_param_list();

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expecting )");

	auto retType = parse_opt_func_type();
	if (retType == nullptr) throw std::runtime_error("Expecting ->");

	return CreateNode<ExternFuncStmt>(id, params, retType);
}

VarDeclExpr* impl::Parser::parse_implicit_var() {
	if (mStream.peek()->type != IDENTIFIER) return nullptr;
	auto name = CreateNode<NamedIDExpr>(mStream.get()->value);

	Type* type = parse_opt_type_spec();
	Expression* value = nullptr;

	if (mStream.peek()->type == ASSIGN) {
		mStream.get();

		value = parse_expression();
		if (value == nullptr) throw std::runtime_error("Expected expression");
	}

	std::vector<Identifier*> bindings;
	bindings.push_back(name);

	std::vector<Type*> types;
	if (type != nullptr) types.push_back(type);

	return CreateNode<VarDeclExpr>(bindings, types, value);
}

Type* impl::Parser::parse_opt_type_spec() {
	if (mStream.peek()->type != COLON) return nullptr;
	mStream.get();

	auto type = parse_type();
	if (type == nullptr) throw std::runtime_error("Expected type");

	return type;
}

AggregateStmt* impl::Parser::parse_aggregate() {
	if (mStream.peek()->type != AGGREGATE) return nullptr;
	mStream.get();

	auto id = parse_identifier();

	auto block = parse_long_block();
	if (block == nullptr) throw std::runtime_error("Expected {");

	return CreateNode<AggregateStmt>(id, block);
}

InterfaceStmt* impl::Parser::parse_interface() {
	if (mStream.peek()->type != INTERFACE) return nullptr;
	mStream.get();

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	auto block = parse_long_block();
	if (block == nullptr) throw std::runtime_error("Expected {");

	return CreateNode<InterfaceStmt>(id, block);
}

NamespaceStmt* impl::Parser::parse_namespace() {
	if (mStream.peek()->type != NAMESPACE) return nullptr;
	mStream.get();

	auto id = parse_full_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	auto block = parse_long_block();

	return CreateNode<NamespaceStmt>(id, block);
}

ImportStmt* impl::Parser::parse_import() {
	if (mStream.peek()->type != IMPORT) return nullptr;
	mStream.get();

	auto id = parse_full_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	return CreateNode<ImportStmt>(id);
}

ExtendStmt* impl::Parser::parse_extension() {
	if (mStream.peek()->type != EXTEND) return nullptr;
	mStream.get();

	auto id = parse_full_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	auto supers = parse_opt_supers();

	auto block = parse_long_block();
	if (block == nullptr) throw std::runtime_error("Expected {");

	return CreateNode<ExtendStmt>(id, supers, block);
}

PropertyStmt* impl::Parser::parse_property() {
	auto pos = mStream.tell();
	auto flags = parse_flags();
	auto propertyStmt = parse_property_base();

	if (propertyStmt == nullptr) {
		mStream.seek(pos);
		return nullptr;
	}

	propertyStmt->flags.insert(propertyStmt->flags.end(), flags.begin(), flags.end());
	return propertyStmt;
}

PropertyStmt* impl::Parser::parse_property_base() {
	if (mStream.peek()->type != PROPERTY) return nullptr;
	mStream.get();

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	auto type = parse_opt_func_type();
	auto block = parse_block();

	return CreateNode<PropertyStmt>(id, type, block);
}

ExprStmt* impl::Parser::parse_expr_statement() {
	auto pos = mStream.tell();

	auto expr = parse_expression();
	if (expr == nullptr) return nullptr;

	if (mStream.peek()->type != SEMICOLON) {
		mStream.seek(pos);
		return nullptr;
	}

	return CreateNode<ExprStmt>(expr);
}

GetterStmt* impl::Parser::parse_getter() {
	if (mStream.peek()->type != GET) return nullptr;
	mStream.get();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<GetterStmt>(block);
}

SetterStmt* impl::Parser::parse_setter() {
	if (mStream.peek()->type != SET) return nullptr;
	mStream.get();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<SetterStmt>(block);
}

/*
 * Expressions
 */

Expression* impl::Parser::parse_expression() {
	auto LHS = parse_unary();
	if (LHS == nullptr) return nullptr;

	auto expr = parse_expression_1(LHS, 0);
	if (expr == nullptr) return nullptr;

	if (mStream.peek()->type == AS) {
		mStream.get();

		auto type = parse_type();
		if (type == nullptr) throw std::runtime_error("Expected type");

		expr = CreateNode<CastExpr>(type, expr);
	}

	return expr;
}

Expression* impl::Parser::parse_expression_1(Expression* LHS, int min_precedence) {
	auto next = mStream.peek();

	while (GetOperatorPrecedence(next->type) >= min_precedence) {
		auto op = next->type;
		mStream.get();

		// Bail early if we found a question mark to properly handle ternary operators
		if (op == QUESTION) {
			auto trueValue = parse_expression();

			if (mStream.get()->type != COLON)
				throw std::runtime_error("Expected :");

			auto falseValue = parse_expression();

			LHS = CreateNode<TernaryExpr>(LHS, trueValue, falseValue);
		}

		auto RHS = parse_unary();
		if (RHS == nullptr) throw std::runtime_error("Expected expression");

		next = mStream.peek();

		while ((GetAssociativity(next->type) == RIGHT &&
				GetOperatorPrecedence(next->type) > GetOperatorPrecedence(op)) ||
			   (GetAssociativity(next->type) == LEFT &&
				GetOperatorPrecedence(next->type) == GetOperatorPrecedence(op))) {
			RHS = parse_expression_1(RHS, GetOperatorPrecedence(next->type));
			next = mStream.peek();
		}

		LHS = CreateNode<BinOpExpr>(LHS, GetBinOp(op), RHS);
	}

	return LHS;
}

Expression* impl::Parser::parse_unary() {
	if (mStream.eof()) return nullptr;

	Expression* inner = nullptr;
	auto lookahead = mStream.peek();

	switch (lookahead->type) {
		case TokenType::INCREMENT:
		case TokenType::DECREMENT:
		case TokenType::MINUS:
		case TokenType::NOT:
		case TokenType::TILDE:
		case TokenType::TIMES:
		case TokenType::BIT_AND:
			mStream.get();
			inner = parse_unary();
			if (inner == nullptr) throw std::runtime_error("Expected expression");
			return CreateNode<UnaryExpr>(GetUnaryOp(lookahead->type), UnaryOrder::PREFIX, inner);
		default: break;
	}

	return parse_values();
}

Expression* impl::Parser::parse_values() {
	auto LHS = parse_primary();
	if (LHS == nullptr) return nullptr;

	while (!mStream.eof()) {
		auto lookahead = mStream.peek();

		if (lookahead->type == OPEN_PAREN) { // function
			mStream.get();

			auto args = parse_arg_list();

			if (mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			LHS = CreateNode<FunctionCallExpr>(LHS, args);
		} else if (lookahead->type == OPEN_BRACKET) { // array access
			mStream.get();

			auto index = parse_expression();

			if (mStream.get()->type != CLOSE_BRACKET)
				throw std::runtime_error("Expected ]");

			LHS = CreateNode<ArrayAccessExpr>(LHS, index);
		} else if (lookahead->type == INCREMENT) { // increment
			mStream.get();
			LHS = CreateNode<UnaryExpr>(UnaryOp::INCREMENT, UnaryOrder::POSTFIX, LHS);
		} else if (lookahead->type == DECREMENT) { // decrement
			mStream.get();
			LHS = CreateNode<UnaryExpr>(UnaryOp::DECREMENT, UnaryOrder::POSTFIX, LHS);
		} else if (lookahead->type == DOT) {
			mStream.get();

			auto id = parse_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			LHS = CreateNode<MemberAccessExpr>(LHS, id);
		} else break;
	}

	return LHS;
}

Expression* impl::Parser::parse_primary() { return parse_value(); }

Expression* impl::Parser::parse_value() {
	Expression* expr = nullptr;

	if ((expr = parse_constant_val()) != nullptr) return expr;
	if ((expr = parse_array_expression()) != nullptr) return expr;
	if ((expr = parse_inclusive_range_expr()) != nullptr) return expr;
	if ((expr = parse_exclusive_range_expr()) != nullptr) return expr;
	if ((expr = parse_tuple_expr()) != nullptr) return expr;
	if ((expr = parse_this()) != nullptr) return expr;
	if ((expr = parse_control()) != nullptr) return expr;
	if ((expr = parse_new()) != nullptr) return expr;

	return nullptr;
}

/// TODO: this doesn't retain the type
Value* impl::Parser::parse_constant_val() {
	auto lookahead = mStream.peek();

	if (IsIntToken(lookahead)) {
		auto value = ToInt(mStream.get());
		return CreateNode<IntValue>(value);
	} else if (IsUIntToken(lookahead)) {
		auto value = ToUInt(mStream.get());
		return CreateNode<UIntValue>(value);
	} else if (lookahead->type == VAL_FLOAT) {
		auto value = ToFloat(mStream.get());
		return CreateNode<FloatValue>(value);
	} else if (lookahead->type == VAL_DOUBLE) {
		auto value = ToDouble(mStream.get());
		return CreateNode<DoubleValue>(value);
	} else if (lookahead->type == VAL_CHAR) {
		auto value = mStream.get()->value[0];
		return CreateNode<CharValue>(value);
	} else if (lookahead->type == VAL_STRING) {
		auto value = mStream.get()->value;
		return CreateNode<StringValue>(value);
	}

	return nullptr;
}

Expression* impl::Parser::parse_this() {
	if (mStream.peek()->type != THIS) return nullptr;
	return CreateNode<ThisID>();
}

Expression* impl::Parser::parse_control() {
	Expression* ctrl = nullptr;

	if ((ctrl = parse_if()) != nullptr) return ctrl;
	if ((ctrl = parse_switch()) != nullptr) return ctrl;
	if ((ctrl = parse_try_block()) != nullptr) return ctrl;

	return nullptr;
}

NewExpr* impl::Parser::parse_new() {
	if (mStream.peek()->type != NEW) return nullptr;
	mStream.get();

	auto full_id = parse_full_identifier();
	return CreateNode<NewExpr>(full_id);
}

// Parse an array expression, but bail if we run into an inclusive/exclusive range token
ArrayExpr* impl::Parser::parse_array_expression() {
	auto pos = mStream.tell();

	if (mStream.peek()->type != OPEN_BRACKET) return nullptr;
	mStream.get();

	std::vector<Expression *> elements;

	auto element = parse_expression();
	if (element == nullptr && mStream.peek()->type != CLOSE_BRACKET)
		throw std::runtime_error("Expected expression");
	if (element != nullptr) elements.push_back(element);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto element = parse_expression();
		if (element == nullptr) throw std::runtime_error("Expected expression");
		elements.push_back(element);
	}

	if (mStream.get()->type != CLOSE_BRACKET) {
		if (mStream.get()->type == EXCLUSIVE_RANGE || mStream.get()->type == INCLUSIVE_RANGE) {
			mStream.seek(pos);
			return nullptr;
		}

		throw std::runtime_error("Expected ]");
	}

	return CreateNode<ArrayExpr>(elements);
}

ArrayRangeExpr* impl::Parser::parse_inclusive_range_expr() {
	auto pos = mStream.tell();

	if (mStream.peek()->type != OPEN_BRACKET) return nullptr;
	mStream.get();

	auto LHS = parse_expression();
	if (LHS == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != INCLUSIVE_RANGE) {
		mStream.seek(pos);
		return nullptr;
	}

	auto RHS = parse_expression();
	if (RHS == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_BRACKET) {
		throw std::runtime_error("Expected ]");
	}

	return CreateNode<ArrayRangeExpr>(LHS, ArrayRangeType::INCLUSIVE, RHS);
}

ArrayRangeExpr* impl::Parser::parse_exclusive_range_expr() {
	auto pos = mStream.tell();

	if (mStream.peek()->type != OPEN_BRACKET) return nullptr;
	mStream.get();

	auto LHS = parse_expression();
	if (LHS == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != EXCLUSIVE_RANGE) {
		mStream.seek(pos);
		return nullptr;
	}

	auto RHS = parse_expression();
	if (RHS == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_BRACKET) {
		throw std::runtime_error("Expected ]");
	}

	return CreateNode<ArrayRangeExpr>(LHS, ArrayRangeType::EXCLUSIVE, RHS);
}

/// Also parses (expression) as just an expression. A trailing comma
/// is required to make it a tuple.
Expression* impl::Parser::parse_tuple_expr() {
	if (mStream.peek()->type != OPEN_PAREN) return nullptr;
	mStream.get();

	std::vector<Expression*> exprs;
	bool isTuple = false;

	auto expr = parse_tuple_value();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	while (mStream.peek()->type == COMMA) {
		mStream.get();
		isTuple = true;

		auto expr = parse_tuple_value();
		if (expr != nullptr) exprs.push_back(expr);
		else break;
	}

	if (mStream.get()->type != CLOSE_PAREN) throw std::runtime_error("Expected )");

	if (!isTuple) {
		if (isA<NamedExpr>(exprs[0]))
			throw std::runtime_error("Unexpected named expression for non-tuple");

		return exprs[0];
	}
	else return CreateNode<TupleExpr>(exprs);
}

Expression* impl::Parser::parse_tuple_value() {
	Expression* val = nullptr;
	if ((val = parse_named_expr()) != nullptr) return val;

	return parse_expression();
}

NamedExpr* impl::Parser::parse_named_expr() {
	auto pos = mStream.tell();
	if (mStream.peek()->type != IDENTIFIER) return nullptr;

	auto name = mStream.get()->value;

	if (mStream.get()->type != COLON) {
		mStream.seek(pos);
		return nullptr;
	}

	auto value = parse_expression();
	if (value == nullptr) throw std::runtime_error("Expected expression");

	return CreateNode<NamedExpr>(CreateNode<NamedIDExpr>(name), value);
}

IfExpr* impl::Parser::parse_if() {
	if (mStream.peek()->type != IF) return nullptr;
	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	auto blocks = parse_elif_or_else();
	blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

	return CreateNode<IfExpr>(blocks);
}

std::vector<ConditionalBlock*> impl::Parser::parse_elif_or_else() {
	std::vector<ConditionalBlock*> blocks;

	if (mStream.peek()->type != ELIF) {
		auto elseBlock = parse_else();
		if (elseBlock != nullptr) blocks.push_back(elseBlock);
		return blocks;
	}

	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	blocks = parse_elif_or_else();
	blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

	return blocks;
}

ConditionalBlock* impl::Parser::parse_else() {
	if (mStream.peek()->type != ELSE) return nullptr;
	mStream.get();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<ConditionalBlock>(nullptr, block);
}

Expression* impl::Parser::parse_for_component() {
	Expression* expr = nullptr;

	if ((expr = parse_var_decl()) != nullptr) return expr;
	if ((expr = parse_expression()) != nullptr) return expr;

	return expr;
}

LoopStmt* impl::Parser::parse_for_loop() {
	if (mStream.peek()->type != FOR) return nullptr;
	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto initializer = parse_for_component();

	if (mStream.get()->type != SEMICOLON) throw std::runtime_error("Expected ;");

	auto condition = parse_for_component();

	if (mStream.get()->type != SEMICOLON) throw std::runtime_error("Expected ;");

	auto afterthought = parse_for_component();

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto body = parse_block();
	if (body == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<LoopStmt>(initializer, condition, afterthought, LoopConditionCheck::BEFORE, body);
}

ForeachStmt* impl::Parser::parse_foreach() {
	if (mStream.peek()->type != FOREACH) return nullptr;
	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto var_decl = parse_var_decl();
	if (var_decl == nullptr) throw std::runtime_error("Expected variable declaration");

	if (mStream.get()->type != IN) throw std::runtime_error("Expected in");

	auto value = parse_expression();
	if (value == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto body = parse_block();
	if (body == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<ForeachStmt>(var_decl, value, body);
}

LoopStmt* impl::Parser::parse_while() {
	if (mStream.peek()->type != WHILE) return nullptr;
	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto condition = parse_for_component();
	if (condition == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto body = parse_block();
	if (body == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<LoopStmt>(nullptr, condition, nullptr, LoopConditionCheck::BEFORE, body);
}

LoopStmt* impl::Parser::parse_forever() {
	if (mStream.peek()->type != FOREVER) return nullptr;
	mStream.get();

	auto body = parse_block();
	if (body == nullptr) throw std::runtime_error("Expected block");

	return CreateNode<LoopStmt>(nullptr, nullptr, nullptr, LoopConditionCheck::BEFORE, body);
}

LoopStmt* impl::Parser::parse_do_while() {
	if (mStream.peek()->type != DO) return nullptr;
	mStream.get();

	auto body = parse_block();
	if (body == nullptr) throw std::runtime_error("Expected block");

	if (mStream.get()->type != WHILE)
		throw std::runtime_error("Expected while");

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto condition = parse_for_component();
	if (condition == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	return CreateNode<LoopStmt>(nullptr, condition, nullptr, LoopConditionCheck::AFTER, body);
}

SwitchExpr* impl::Parser::parse_switch() {
	if (mStream.peek()->type != SWITCH) return nullptr;
	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto expression = parse_expression();
	if (expression == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	auto block = parse_switch_block();
	return CreateNode<SwitchExpr>(expression, block);
}

std::vector<SwitchPattern*> impl::Parser::parse_switch_block() {
	if (mStream.get()->type != OPEN_CURLY)
		throw std::runtime_error("Expected {");

	return parse_switch_matches();

	if (mStream.get()->type != CLOSE_CURLY)
		throw std::runtime_error("Expected }");
}

std::vector<SwitchPattern*> impl::Parser::parse_switch_matches() {
	std::vector<SwitchPattern*> matches;

	auto match = parse_switch_match();
	if (match == nullptr) return matches;
	matches.push_back(match);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		match = parse_switch_match();
		if (match == nullptr) throw std::runtime_error("Expected switch pattern");
		matches.push_back(match);
	}

	return matches;
}

SwitchPattern* impl::Parser::parse_switch_match() {
	auto patterns = parse_switch_patterns();
	if (patterns.size() == 0) return nullptr;

	if (mStream.get()->type != COLON)
		throw std::runtime_error("Expected :");

	auto val = parse_switch_value();
	if (val == nullptr) throw std::runtime_error("Expected switch value");

	return CreateNode<SwitchPattern>(patterns, val);
}

std::vector<Expression*> impl::Parser::parse_switch_patterns() {
	std::vector<Expression*> pattern_list;

	auto pattern = parse_switch_pattern();
	if (pattern == nullptr) return pattern_list;
	pattern_list.push_back(pattern);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		pattern = parse_switch_pattern();
		if (pattern == nullptr) throw std::runtime_error("Expected switch pattern");
		pattern_list.push_back(pattern);
	}

	return pattern_list;
}

Expression* impl::Parser::parse_switch_pattern() { return parse_expression(); }

BlockExpr* impl::Parser::parse_switch_value() {
	auto long_block = parse_long_block();
	if (long_block != nullptr) return long_block;

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expecting block or expression");

	return CreateNode<ShortBlockExpr>(expr);
}

BreakStmt* impl::Parser::parse_break_stmt() {
	if (mStream.peek()->type != BREAK) return nullptr;
	mStream.get();
	return CreateNode<BreakStmt>();
}

ContinueStmt* impl::Parser::parse_continue_stmt() {
	if (mStream.peek()->type != CONTINUE) return nullptr;
	mStream.get();
	return CreateNode<ContinueStmt>();
}

YieldStmt* impl::Parser::parse_yield_stmt() {
	if (mStream.peek()->type != YIELD) return nullptr;
	mStream.get();

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	return CreateNode<YieldStmt>(expr);
}

std::vector<Expression*> impl::Parser::parse_arg_list() {
	std::vector<Expression*> arg_list;

	auto argument = parse_arg();
	if (argument == nullptr) return arg_list;
	arg_list.push_back(argument);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto argument = parse_arg();
		if (argument == nullptr) throw std::runtime_error("Expected argument");
		arg_list.push_back(argument);
	}

	return arg_list;
}

Expression* impl::Parser::parse_arg() {
	Expression* expr = nullptr;
	if ((expr = parse_named_expr()) != nullptr) return expr;

	return parse_expression();
}


Generics* impl::Parser::parse_generics() {
	if (mStream.peek()->type != LESS_THAN) return nullptr;
	mStream.get();

	auto values = parse_generic_values();
	auto constraints = parse_opt_constraints();

	if (mStream.get()->type != GREATER_THAN)
		throw std::runtime_error("Expected >");

	return CreateNode<Generics>(values, constraints);
}

std::vector<Identifier*> impl::Parser::parse_generic_values() {
	std::vector<Identifier*> id_list;

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");
	id_list.push_back(id);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		auto id = parse_identifier();
		if (id == nullptr) throw std::runtime_error("Expected identifier");
		id_list.push_back(id);
	}

	return id_list;
}

std::vector<Constraint*> impl::Parser::parse_opt_constraints() {
	if (mStream.peek()->type != COLON)
		return std::vector<Constraint*>();

	mStream.get();
	return parse_constraints();
}

std::vector<Constraint*> impl::Parser::parse_constraints() {
	std::vector<Constraint*> constraint_list;

	auto constraint = parse_constraint();
	if (constraint == nullptr) throw std::runtime_error("Expected constraint");
	constraint_list.push_back(constraint);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		constraint = parse_constraint();
		if (constraint == nullptr) throw std::runtime_error("Expected constraint");
		constraint_list.push_back(constraint);
	}

	return constraint_list;
}

Constraint* impl::Parser::parse_constraint() {
	if (mStream.peek()->type != WHERE) return nullptr;
	mStream.get();

	auto id = parse_identifier();
	if (id == nullptr) throw std::runtime_error("Expected identifier");

	if (mStream.get()->type != ASSIGN)
		throw std::runtime_error("Expected =");

	auto constraint = parse_type_constraint(id);
	if (constraint == nullptr) throw std::runtime_error("Expected constraint value");

	return constraint;
}

Constraint* impl::Parser::parse_type_constraint(Identifier* id) {
	if (mStream.eof()) return nullptr;

	auto lookahead = mStream.peek();

	if (lookahead->type == CLASS) {
		mStream.get();
		return CreateNode<ClassConstraint>(id);
	} else if (lookahead->type == NEW) {
		mStream.get();

		if (mStream.get()->type != OPEN_PAREN)
			throw std::runtime_error("Expected (");

		if (mStream.get()->type != CLOSE_PAREN)
			throw std::runtime_error("Expected )");

		return CreateNode<DefaultCtorConstraint>(id);
	} else if (lookahead->type == DATA) {
		mStream.get();

		auto type = parse_type();
		if (type == nullptr) throw std::runtime_error("Expected type");

		return CreateNode<DataConstraint>(id, type);
	}

	auto base = parse_identifier();
	if (id != nullptr) {
		return CreateNode<BaseConstraint>(id, base);
	}

	auto type = parse_type();
	if (type != nullptr) {
		return CreateNode<TypeConstraint>(id, type);
	}

	return nullptr;
}

DeleteStmt* impl::Parser::parse_delete() {
	if (mStream.peek()->type != DELETE) return nullptr;
	mStream.get();

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	return CreateNode<DeleteStmt>(expr);
}

std::vector<Flag*> impl::Parser::parse_flags() {
	std::vector<Flag*> flags;

	while (mStream.eof()) {
		Flag* flag = parse_flag();

		if (flag != nullptr) {
			flags.push_back(flag);
			continue;
		}

		break;
	}

	return flags;
}

Flag* impl::Parser::parse_flag() {
	Flag* flag = nullptr;

	if ((flag = parse_virtual()) != nullptr) return flag;
	if ((flag = parse_privacy()) != nullptr) return flag;
	if ((flag = parse_partial()) != nullptr) return flag;

	return flag;
}

Flag* impl::Parser::parse_virtual() {
	if (mStream.peek()->type != VIRTUAL) return nullptr;
	mStream.get();

	return new VirtualFlag();
}

Flag* impl::Parser::parse_privacy() {
	if (mStream.eof()) return nullptr;

	switch (mStream.peek()->type) {
		case TokenType::PRIVATE:
			mStream.get();
			return new PrivacyFlag(PrivacyLevel::PRIVATE);
		case TokenType::PROTECTED:
			mStream.get();
			return new PrivacyFlag(PrivacyLevel::PROTECTED);
		case TokenType::PUBLIC:
			mStream.get();
			return new PrivacyFlag(PrivacyLevel::PUBLIC);
		default: return nullptr;
	}
}

Flag* impl::Parser::parse_partial() {
	if (mStream.peek()->type != PARTIAL) return nullptr;
	mStream.get();

	return new PartialFlag();
}

TryExpr* impl::Parser::parse_try_block() {
	if (mStream.peek()->type != TRY) return nullptr;
	mStream.get();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	auto catches = parse_catch_blocks();
	auto finally = parse_finally_block();

	return CreateNode<TryExpr>(block, catches, finally);
}

std::vector<CatchBlock*> impl::Parser::parse_catch_blocks() {
	std::vector<CatchBlock*> catches;

	while (mStream.peek()->type == CATCH) {
		if (mStream.peek()->type != CATCH) return catches;
		mStream.get();

		if (mStream.get()->type != OPEN_PAREN)
			throw std::runtime_error("Expected (");

		auto exception = parse_var_decl();
		if (exception == nullptr) throw std::runtime_error("Expected expression");

		if (mStream.get()->type != CLOSE_PAREN)
			throw std::runtime_error("Expected )");

		auto block = parse_block();
		if (block == nullptr) throw std::runtime_error("Expected block");

		auto catch_block = CreateNode<CatchBlock>(exception, block);
		catches.push_back(catch_block);
	}

	return catches;
}

BlockExpr* impl::Parser::parse_finally_block() {
	if (mStream.peek()->type != FINALLY) return nullptr;
	mStream.get();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	return block;
}

ThrowStmt* impl::Parser::parse_throw_stmt() {
	if (mStream.peek()->type != THROW) return nullptr;
	mStream.get();

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	return CreateNode<ThrowStmt>(expr);
}

orange::ast::LongBlockExpr* impl::Parser::parse() {
	auto stmts = parse_statements(true);
	return CreateNode<LongBlockExpr>(stmts);
}

LongBlockExpr* orange::parser::Parser::parse() { return mParserImpl->parse(); }
orange::parser::Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) { }
