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

namespace orange { namespace parser { namespace impl {
	using namespace orange::ast;

	int GetOperatorPrecedence(TokenType tok) {
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

	enum OperatorAssociativity { LEFT, RIGHT };

	OperatorAssociativity GetAssociativity(TokenType tok) {
		auto prec = GetOperatorPrecedence(tok);

		if (prec == 13) return OperatorAssociativity::RIGHT;
		else return OperatorAssociativity::LEFT;
	}

	UnaryOp GetUnaryOp(TokenType ty) {
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

	BinOp GetBinOp(TokenType ty) {
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

	class Parser {
	private:
		LexStream mStream;

		bool isTerm(Token* tok) { return tok->type == NEWLINE || tok->type == SEMICOLON; }
		bool checkNext(TokenType ty) { return mStream.peek() != nullptr && mStream.peek()->type == ty; }

		std::vector<Node *> parse_opt_statements() {
			return parse_statements(true);
		}

		std::vector<Node *> parse_statements(bool allow_eps = false) {
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

		Token* parse_term() {
			if (!isTerm(mStream.peek())) return nullptr;
			return mStream.get();
		}

		LongBlockExpr* parse_long_block() {
			if (checkNext(OPEN_CURLY) == false) return nullptr;
			mStream.get();

			auto stmts = parse_opt_statements();

			if (checkNext(CLOSE_CURLY) == false) throw std::runtime_error("Expected }");

			return CreateNode<LongBlockExpr>(stmts);
		}

		ShortBlockExpr* parse_short_block() {
			if (checkNext(COLON) == false) return nullptr;

			auto stmt = parse_statement();
			if (stmt == nullptr) throw std::runtime_error("Expected statement");

			return CreateNode<ShortBlockExpr>(stmt);
		}

		BlockExpr* parse_block() {
			BlockExpr* block = nullptr;

			if ((block = parse_long_block()) != nullptr) return block;
			if ((block = parse_short_block()) != nullptr) return block;

			throw std::runtime_error("Expected block");
		}

		/*
		 * Types
		 */

		Type* parse_type() {
			return parse_complex_type();
		}

		Type* parse_basic_type() {
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

		Type* parse_complex_type() {
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

						if (mStream.eof() || mStream.get()->type != CLOSE_BRACKET)
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

		Type* parse_complex_type_base() {
			Type* ty = nullptr;

			if ((ty = parse_basic_type()) != nullptr) return ty;
			if ((ty = parse_tuple_or_func_type()) != nullptr) return ty;
			if ((ty = parse_base_id_type()) != nullptr) return ty;

			return nullptr;
		}

		Type* parse_tuple_or_func_type() {
			if (mStream.eof() || mStream.peek()->type != OPEN_PAREN) return nullptr;
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

			if (mStream.eof() || mStream.peek()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			if (trailingComma == false && mStream.eof() == false && mStream.peek()->type == ARROW) {
				mStream.get();

				auto returnTy = parse_type();
				if (returnTy == nullptr) throw std::runtime_error("Expected return type");

				return new FunctionType(types, returnTy);
			} else {
				return new TupleType(types);
			}
		}

		Type* parse_base_id_type() {
			if (!mStream.eof() && mStream.peek()->type == IDENTIFIER) {
				return new IdentifierType(CreateNode<NamedIDExpr>(mStream.peek()->value));
			}

			Type* ty = nullptr;

			if ((ty = parse_operator_id_ty()) != nullptr) return ty;

			return nullptr;
		}

		Type* parse_operator_id_ty() {
			if (mStream.eof() || mStream.peek()->type != OPERATOR) return nullptr;
			throw std::runtime_error("Don't know how to parse operators yet");
		}

		/*
		 * Identifier
		 */

		Identifier* parse_identifier() {
			auto id = parse_identifier_base();
			if (id == nullptr) return nullptr;

			auto generics = parse_opt_generic_spec();
			if (generics == nullptr) throw std::runtime_error("Don't know how to use generics in IDs yet");

			return id;
		}

		Generics* parse_opt_generic_spec() {
			if (mStream.eof() || mStream.peek()->type != LESS_THAN) return nullptr;
			throw std::runtime_error("Don't know how to parse generic IDs yet");
		}

		Identifier* parse_identifier_base() {
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

		Identifier* parse_full_identifier() {
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

		Node* parse_statement() {
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

		VarDeclExpr* parse_var_decl() {
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

		Flag* parse_opt_const() {
			if (mStream.eof() || mStream.peek()->type != CONST) return nullptr;
			return new ConstFlag();
		}

		std::vector<Identifier*> parse_identifiers() {
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

		std::vector<Identifier*> parse_identifier_list() {
			std::vector<Identifier*> ids;

			auto id = parse_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");
			ids.push_back(id);

			while (mStream.eof() == false && mStream.peek()->type == COMMA) {
				auto id = parse_identifier();
				if (id == nullptr) throw std::runtime_error("Expected identifier");
				ids.push_back(id);
			}

			return ids;
		}

		std::vector<Type*> parse_opt_type_spec_list() {
			std::vector<Type*> tys;
			if (mStream.eof() || mStream.peek()->type != COLON) return tys;
			mStream.get();

			auto ty = parse_type();
			if (ty == nullptr) throw std::runtime_error("Expected type");
			tys.push_back(ty);

			while (mStream.eof() == false && mStream.peek()->type == COMMA) {
				auto ty = parse_type();
				if (ty == nullptr) throw std::runtime_error("Expected type");
				tys.push_back(ty);
			}

			return tys;
		}

		Expression* parse_opt_value() {
			if (mStream.eof() || mStream.peek()->type != ASSIGN) return nullptr;
			mStream.get();
			return parse_expression();
		}

		EnumStmt* parse_enum() {
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

		EnumStmt* parse_enum_base() {
			if (mStream.eof() || mStream.peek()->type != ENUM) return nullptr;
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

		std::vector<EnumValue*> parse_enum_values() {
			std::vector<EnumValue*> values;

			auto value = parse_enum_value();
			if (value == nullptr) return values;
			values.push_back(value);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				auto value = parse_enum_value();
				if (value == nullptr) throw std::runtime_error("Expected enumeration value");
				values.push_back(value);
			}

			return values;
		}

		EnumValue* parse_enum_value() {
			if (mStream.eof() || mStream.peek()->type != IDENTIFIER) return nullptr;

			auto name = mStream.get()->value;
			std::vector<VarDeclExpr*> params = parse_opt_enum_params();

			return CreateNode<EnumValue>(CreateNode<NamedIDExpr>(name), params);
		}

		std::vector<VarDeclExpr*> parse_opt_enum_params() {
			std::vector<VarDeclExpr*> params;
			if (mStream.eof() || mStream.peek()->type != OPEN_PAREN) return params;
			mStream.get();

			params = parse_param_list();

			if (mStream.get()->type == CLOSE_PAREN) throw std::runtime_error("Expected )");
			return params;
		}


		ClassStmt* parse_class() {
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

		ClassStmt* parse_base_class() {
			if (mStream.eof() || mStream.peek()->type != CLASS) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.peek()->type != IDENTIFIER)
				throw std::runtime_error("Expected identifier");

			auto name = CreateNode<NamedIDExpr>(mStream.get()->value);
			auto supers = parse_opt_supers();
			auto body = parse_class_body();

			return CreateNode<ClassStmt>(name, supers, body);
		}

		std::vector<Identifier*> parse_opt_supers() {
			std::vector<Identifier*> ids;
			if (mStream.eof() || mStream.peek()->type != COLON) return ids;

			auto id = parse_full_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");
			ids.push_back(id);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				auto id = parse_full_identifier();
				if (id == nullptr) throw std::runtime_error("Expected identifier");
				ids.push_back(id);
			}

			return ids;
		}

		ClassStmt* parse_partial_class() {
			auto pos = mStream.tell();
			auto flags = parse_flags();

			if (mStream.eof() || mStream.peek()->type != PARTIAL) {
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

		LongBlockExpr* parse_class_body() {
			if (mStream.eof() || mStream.peek()->type != OPEN_CURLY)
				throw std::runtime_error("Expected {");

			auto stmts = parse_class_stmts();

			if (mStream.eof() || mStream.peek()->type != CLOSE_CURLY)
				throw std::runtime_error("Expected }");

			return CreateNode<LongBlockExpr>(stmts);
		}

		std::vector<Node*> parse_class_stmts() {
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

		Node* parse_class_stmt() {
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

		FunctionExpr* parse_function() {
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

		FunctionExpr* parse_base_function() {
			if (mStream.eof() || mStream.peek()->type != DEF) return nullptr;
			mStream.get();

			auto id = parse_identifier();
			auto generics = parse_generics();

			if (mStream.eof() || mStream.peek()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto params = parse_param_list();

			if (mStream.eof() || mStream.peek()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto retType = parse_opt_func_type();
			auto body = parse_block();

			return CreateNode<FunctionExpr>(id, generics, params, retType, body);
		}

		std::vector<VarDeclExpr*> parse_param_list() {
			std::vector<VarDeclExpr*> params;

			auto param = parse_implicit_var();
			if (param == nullptr) return params;
			params.push_back(param);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				auto param = parse_implicit_var();
				if (param == nullptr) return params;
				params.push_back(param);
			}

			return params;
		}

		Type* parse_opt_func_type() {
			if (mStream.eof() || mStream.peek()->type != ARROW) return nullptr;
			mStream.get();

			return parse_type();
		}

		ExternFuncStmt* parse_extern_fn() {
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

		ExternFuncStmt* parse_base_extern() {
			if (mStream.eof() || mStream.peek()->type != EXTERN) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != DEF)
				throw std::runtime_error("Expecting def");

			auto id = parse_identifier();
			if (id == nullptr) throw std::runtime_error("Expecting identifier");

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expecting (");

			auto params = parse_param_list();

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expecting )");

			auto retType = parse_opt_func_type();
			if (retType == nullptr) throw std::runtime_error("Expecting ->");

			return CreateNode<ExternFuncStmt>(id, params, retType);
		}

		VarDeclExpr* parse_implicit_var() {
			if (mStream.eof() || mStream.peek()->type != IDENTIFIER) return nullptr;
			auto name = CreateNode<NamedIDExpr>(mStream.get()->value);

			Type* type = parse_opt_type_spec();
			Expression* value = nullptr;

			if (!mStream.eof() && mStream.peek()->type == ASSIGN) {
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

		Type* parse_opt_type_spec() {
			if (mStream.eof() || mStream.peek()->type != COLON) return nullptr;
			mStream.get();

			auto type = parse_type();
			if (type == nullptr) throw std::runtime_error("Expected type");

			return type;
		}

		AggregateStmt* parse_aggregate() {
			if (mStream.eof() || mStream.peek()->type != AGGREGATE) return nullptr;
			mStream.get();

			auto id = parse_identifier();

			auto block = parse_long_block();
			if (block == nullptr) throw std::runtime_error("Expected {");

			return CreateNode<AggregateStmt>(id, block);
		}

		InterfaceStmt* parse_interface() {
			if (mStream.eof() || mStream.peek()->type != INTERFACE) return nullptr;
			mStream.get();

			auto id = parse_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			auto block = parse_long_block();
			if (block == nullptr) throw std::runtime_error("Expected {");

			return CreateNode<InterfaceStmt>(id, block);
		}

		NamespaceStmt* parse_namespace() {
			if (mStream.eof() || mStream.peek()->type != NAMESPACE) return nullptr;
			mStream.get();

			auto id = parse_full_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			auto block = parse_long_block();

			return CreateNode<NamespaceStmt>(id, block);
		}

		ImportStmt* parse_import() {
			if (mStream.eof() || mStream.peek()->type != IMPORT) return nullptr;
			mStream.get();

			auto id = parse_full_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			return CreateNode<ImportStmt>(id);
		}

		ExtendStmt* parse_extension() {
			if (mStream.eof() || mStream.peek()->type != EXTEND) return nullptr;
			mStream.get();

			auto id = parse_full_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			auto supers = parse_opt_supers();

			auto block = parse_long_block();
			if (block == nullptr) throw std::runtime_error("Expected {");

			return CreateNode<ExtendStmt>(id, supers, block);
		}

		PropertyStmt* parse_property() {
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

		PropertyStmt* parse_property_base() {
			if (mStream.eof() || mStream.peek()->type != PROPERTY) return nullptr;
			mStream.get();

			auto id = parse_identifier();
			if (id == nullptr) throw std::runtime_error("Expected identifier");

			auto type = parse_opt_func_type();
			auto block = parse_block();

			return CreateNode<PropertyStmt>(id, type, block);
		}

		ExprStmt* parse_expr_statement() {
			auto pos = mStream.tell();

			auto expr = parse_expression();
			if (expr == nullptr) return nullptr;

			if (mStream.eof() || mStream.peek()->type != SEMICOLON) {
				mStream.seek(pos);
				return nullptr;
			}

			return CreateNode<ExprStmt>(expr);
		}

		GetterStmt* parse_getter() {
			if (mStream.eof() || mStream.peek()->type != GET) return nullptr;
			mStream.get();

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<GetterStmt>(block);
		}

		SetterStmt* parse_setter() {
			if (mStream.eof() || mStream.peek()->type != SET) return nullptr;
			mStream.get();

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<SetterStmt>(block);
		}

		/*
		 * Expressions
		 */

		Expression* parse_expression() {
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

		Expression* parse_expression_1(Expression* LHS, int min_precedence) {
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

		Expression* parse_unary() {
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

		Expression* parse_values() {
			auto LHS = parse_primary();
			if (LHS == nullptr) return nullptr;

			while (!mStream.eof()) {
				auto lookahead = mStream.peek();

				if (lookahead->type == OPEN_PAREN) { // function
					mStream.get();

					auto args = parse_arg_list();

					if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
						throw std::runtime_error("Expected )");

					LHS = CreateNode<FunctionCallExpr>(LHS, args);
				} else if (lookahead->type == OPEN_BRACKET) { // array access
					mStream.get();

					auto index = parse_expression();

					if (mStream.eof() || mStream.get()->type != CLOSE_BRACKET)
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

		Expression* parse_primary() { return parse_value(); }

		Expression* parse_value() {
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
		Value* parse_constant_val() {
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

		Expression* parse_this() {
			if (mStream.eof() || mStream.peek()->type != THIS) return nullptr;
			return CreateNode<ThisID>();
		}

		Expression* parse_control() {
			Expression* ctrl = nullptr;

			if ((ctrl = parse_if()) != nullptr) return ctrl;
			if ((ctrl = parse_switch()) != nullptr) return ctrl;
			if ((ctrl = parse_try_block()) != nullptr) return ctrl;

			return nullptr;
		}

		NewExpr* parse_new() {
			if (mStream.eof() || mStream.peek()->type != NEW) return nullptr;
			mStream.get();

			auto full_id = parse_full_identifier();
			return CreateNode<NewExpr>(full_id);
		}

		// Parse an array expression, but bail if we run into an inclusive/exclusive range token
		ArrayExpr* parse_array_expression() {
			auto pos = mStream.tell();

			if (mStream.eof() || mStream.peek()->type != OPEN_BRACKET) return nullptr;
			mStream.get();

			std::vector<Expression *> elements;

			auto element = parse_expression();
			if (element == nullptr && mStream.peek()->type != CLOSE_BRACKET)
				throw std::runtime_error("Expected expression");
			if (element != nullptr) elements.push_back(element);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				auto element = parse_expression();
				if (element == nullptr) throw std::runtime_error("Expected expression");
				elements.push_back(element);
			}

			if (mStream.eof() || mStream.get()->type != CLOSE_BRACKET) {
				if (mStream.get()->type == EXCLUSIVE_RANGE || mStream.get()->type == INCLUSIVE_RANGE) {
					mStream.seek(pos);
					return nullptr;
				}

				throw std::runtime_error("Expected ]");
			}

			return CreateNode<ArrayExpr>(elements);
		}

		ArrayRangeExpr* parse_inclusive_range_expr() {
			auto pos = mStream.tell();

			if (mStream.eof() || mStream.peek()->type != OPEN_BRACKET) return nullptr;
			mStream.get();

			auto LHS = parse_expression();
			if (LHS == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != INCLUSIVE_RANGE) {
				mStream.seek(pos);
				return nullptr;
			}

			auto RHS = parse_expression();
			if (RHS == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_BRACKET) {
				throw std::runtime_error("Expected ]");
			}

			return CreateNode<ArrayRangeExpr>(LHS, ArrayRangeType::INCLUSIVE, RHS);
		}

		ArrayRangeExpr* parse_exclusive_range_expr() {
			auto pos = mStream.tell();

			if (mStream.eof() || mStream.peek()->type != OPEN_BRACKET) return nullptr;
			mStream.get();

			auto LHS = parse_expression();
			if (LHS == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != EXCLUSIVE_RANGE) {
				mStream.seek(pos);
				return nullptr;
			}

			auto RHS = parse_expression();
			if (RHS == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_BRACKET) {
				throw std::runtime_error("Expected ]");
			}

			return CreateNode<ArrayRangeExpr>(LHS, ArrayRangeType::EXCLUSIVE, RHS);
		}

		/// Also parses (expression) as just an expression. A trailing comma
		/// is required to make it a tuple.
		Expression* parse_tuple_expr() {
			if (mStream.eof() || mStream.peek()->type != OPEN_PAREN) return nullptr;
			mStream.get();

			std::vector<Expression*> exprs;
			bool isTuple = false;

			auto expr = parse_tuple_value();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();
				isTuple = true;

				auto expr = parse_tuple_value();
				if (expr != nullptr) exprs.push_back(expr);
				else break;
			}

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN) throw std::runtime_error("Expected )");

			if (!isTuple) {
				if (isA<NamedExpr>(exprs[0]))
					throw std::runtime_error("Unexpected named expression for non-tuple");

				return exprs[0];
			}
			else return CreateNode<TupleExpr>(exprs);
		}

		Expression* parse_tuple_value() {
			Expression* val = nullptr;
			if ((val = parse_named_expr()) != nullptr) return val;

			return parse_expression();
		}

		NamedExpr* parse_named_expr() {
			auto pos = mStream.tell();
			if (mStream.eof() || mStream.peek()->type != IDENTIFIER) return nullptr;

			auto name = mStream.get()->value;

			if (mStream.eof() || mStream.get()->type != COLON) {
				mStream.seek(pos);
				return nullptr;
			}

			auto value = parse_expression();
			if (value == nullptr) throw std::runtime_error("Expected expression");

			return CreateNode<NamedExpr>(CreateNode<NamedIDExpr>(name), value);
		}

		IfExpr* parse_if() {
			if (mStream.eof() || mStream.peek()->type != IF) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			auto blocks = parse_elif_or_else();
			blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

			return CreateNode<IfExpr>(blocks);
		}

		std::vector<ConditionalBlock*> parse_elif_or_else() {
			std::vector<ConditionalBlock*> blocks;

			if (mStream.eof() || mStream.peek()->type != ELIF) {
				auto elseBlock = parse_else();
				if (elseBlock != nullptr) blocks.push_back(elseBlock);
				return blocks;
			}

			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			blocks = parse_elif_or_else();
			blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

			return blocks;
		}

		ConditionalBlock* parse_else() {
			if (mStream.eof() || mStream.peek()->type != ELSE) return nullptr;
			mStream.get();

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<ConditionalBlock>(nullptr, block);
		}

		Expression* parse_for_component() {
			Expression* expr = nullptr;

			if ((expr = parse_var_decl()) != nullptr) return expr;
			if ((expr = parse_expression()) != nullptr) return expr;

			return expr;
		}

		LoopStmt* parse_for_loop() {
			if (mStream.eof() || mStream.peek()->type != FOR) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto initializer = parse_for_component();

			if (mStream.eof() || mStream.get()->type != SEMICOLON) throw std::runtime_error("Expected ;");

			auto condition = parse_for_component();

			if (mStream.eof() || mStream.get()->type != SEMICOLON) throw std::runtime_error("Expected ;");

			auto afterthought = parse_for_component();

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto body = parse_block();
			if (body == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<LoopStmt>(initializer, condition, afterthought, LoopConditionCheck::BEFORE, body);
		}

		ForeachStmt* parse_foreach() {
			if (mStream.eof() || mStream.peek()->type != FOREACH) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto var_decl = parse_var_decl();
			if (var_decl == nullptr) throw std::runtime_error("Expected variable declaration");

			if (mStream.eof() || mStream.get()->type != IN) throw std::runtime_error("Expected in");

			auto value = parse_expression();
			if (value == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto body = parse_block();
			if (body == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<ForeachStmt>(var_decl, value, body);
		}

		LoopStmt* parse_while() {
			if (mStream.eof() || mStream.peek()->type != WHILE) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto condition = parse_for_component();
			if (condition == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto body = parse_block();
			if (body == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<LoopStmt>(nullptr, condition, nullptr, LoopConditionCheck::BEFORE, body);
		}

		LoopStmt* parse_forever() {
			if (mStream.eof() || mStream.peek()->type != FOREVER) return nullptr;
			mStream.get();

			auto body = parse_block();
			if (body == nullptr) throw std::runtime_error("Expected block");

			return CreateNode<LoopStmt>(nullptr, nullptr, nullptr, LoopConditionCheck::BEFORE, body);
		}

		LoopStmt* parse_do_while() {
			if (mStream.eof() || mStream.peek()->type != DO) return nullptr;
			mStream.get();

			auto body = parse_block();
			if (body == nullptr) throw std::runtime_error("Expected block");

			if (mStream.eof() || mStream.get()->type != WHILE)
				throw std::runtime_error("Expected while");

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto condition = parse_for_component();
			if (condition == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			return CreateNode<LoopStmt>(nullptr, condition, nullptr, LoopConditionCheck::AFTER, body);
		}

		SwitchExpr* parse_switch() {
			if (mStream.eof() || mStream.peek()->type != SWITCH) return nullptr;
			mStream.get();

			if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
				throw std::runtime_error("Expected (");

			auto expression = parse_expression();
			if (expression == nullptr) throw std::runtime_error("Expected expression");

			if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
				throw std::runtime_error("Expected )");

			auto block = parse_switch_block();
			return CreateNode<SwitchExpr>(expression, block);
		}

		std::vector<SwitchPattern*> parse_switch_block() {
			if (mStream.eof() || mStream.get()->type != OPEN_CURLY)
				throw std::runtime_error("Expected {");

			return parse_switch_matches();

			if (mStream.eof() || mStream.get()->type != CLOSE_CURLY)
				throw std::runtime_error("Expected }");
		}

		std::vector<SwitchPattern*> parse_switch_matches() {
			std::vector<SwitchPattern*> matches;

			auto match = parse_switch_match();
			if (match == nullptr) return matches;
			matches.push_back(match);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				match = parse_switch_match();
				if (match == nullptr) throw std::runtime_error("Expected switch pattern");
				matches.push_back(match);
			}

			return matches;
		}

		SwitchPattern* parse_switch_match() {
			auto patterns = parse_switch_patterns();
			if (patterns.size() == 0) return nullptr;

			if (mStream.eof() || mStream.get()->type != COLON)
				throw std::runtime_error("Expected :");

			auto val = parse_switch_value();
			if (val == nullptr) throw std::runtime_error("Expected switch value");

			return CreateNode<SwitchPattern>(patterns, val);
		}

		std::vector<Expression*> parse_switch_patterns() {
			std::vector<Expression*> pattern_list;

			auto pattern = parse_switch_pattern();
			if (pattern == nullptr) return pattern_list;
			pattern_list.push_back(pattern);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				pattern = parse_switch_pattern();
				if (pattern == nullptr) throw std::runtime_error("Expected switch pattern");
				pattern_list.push_back(pattern);
			}

			return pattern_list;
		}

		Expression* parse_switch_pattern() { return parse_expression(); }

		BlockExpr* parse_switch_value() {
			auto long_block = parse_long_block();
			if (long_block != nullptr) return long_block;

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expecting block or expression");

			return CreateNode<ShortBlockExpr>(expr);
		}

		BreakStmt* parse_break_stmt() {
			if (mStream.eof() || mStream.peek()->type != BREAK) return nullptr;
			mStream.get();
			return CreateNode<BreakStmt>();
		}

		ContinueStmt* parse_continue_stmt() {
			if (mStream.eof() || mStream.peek()->type != CONTINUE) return nullptr;
			mStream.get();
			return CreateNode<ContinueStmt>();
		}

		YieldStmt* parse_yield_stmt() {
			if (mStream.eof() || mStream.peek()->type != YIELD) return nullptr;
			mStream.get();

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			return CreateNode<YieldStmt>(expr);
		}

		std::vector<Expression*> parse_arg_list() {
			std::vector<Expression*> arg_list;

			auto argument = parse_arg();
			if (argument == nullptr) return arg_list;
			arg_list.push_back(argument);

			while (!mStream.eof() && mStream.peek()->type == COMMA) {
				mStream.get();

				auto argument = parse_arg();
				if (argument == nullptr) throw std::runtime_error("Expected argument");
				arg_list.push_back(argument);
			}

			return arg_list;
		}

		Expression* parse_arg() {
			Expression* expr = nullptr;
			if ((expr = parse_named_expr()) != nullptr) return expr;

			return parse_expression();
		}

		Generics* parse_generics();
		std::vector<Identifier*> parse_opt_generic_values();
		std::vector<Identifier*> parse_generic_values();
		std::vector<Identifier*> parse_generic_values_1();
		std::vector<Constraint*> parse_opt_constraints();
		std::vector<Constraint*> parse_constraints();
		std::vector<Constraint*> parse_constraints_1();
		Constraint* parse_constraint();
		Constraint* parse_type_constraint();

		DeleteStmt* parse_delete() {
			if (mStream.eof() || mStream.peek()->type != DELETE) return nullptr;
			mStream.get();

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			return CreateNode<DeleteStmt>(expr);
		}

		std::vector<Flag*> parse_flags() {
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

		Flag* parse_flag() {
			Flag* flag = nullptr;

			if ((flag = parse_virtual()) != nullptr) return flag;
			if ((flag = parse_privacy()) != nullptr) return flag;
			if ((flag = parse_partial()) != nullptr) return flag;

			return flag;
		}

		Flag* parse_virtual() {
			if (mStream.eof() || mStream.peek()->type != VIRTUAL) return nullptr;
			mStream.get();

			return new VirtualFlag();
		}

		Flag* parse_privacy() {
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

		Flag* parse_partial() {
			if (mStream.eof() || mStream.peek()->type != PARTIAL) return nullptr;
			mStream.get();

			return new PartialFlag();
		}

		TryExpr* parse_try_block() {
			if (mStream.eof() || mStream.peek()->type != TRY) return nullptr;
			mStream.get();

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			auto catches = parse_catch_blocks();
			auto finally = parse_finally_block();

			return CreateNode<TryExpr>(block, catches, finally);
		}

		std::vector<CatchBlock*> parse_catch_blocks() {
			std::vector<CatchBlock*> catches;

			while (!mStream.eof() && mStream.peek()->type == CATCH) {
				if (mStream.eof() || mStream.peek()->type != CATCH) return catches;
				mStream.get();

				if (mStream.eof() || mStream.get()->type != OPEN_PAREN)
					throw std::runtime_error("Expected (");

				auto exception = parse_var_decl();
				if (exception == nullptr) throw std::runtime_error("Expected expression");

				if (mStream.eof() || mStream.get()->type != CLOSE_PAREN)
					throw std::runtime_error("Expected )");

				auto block = parse_block();
				if (block == nullptr) throw std::runtime_error("Expected block");

				auto catch_block = CreateNode<CatchBlock>(exception, block);
				catches.push_back(catch_block);
			}

			return catches;
		}

		BlockExpr* parse_finally_block() {
			if (mStream.eof() || mStream.peek()->type != FINALLY) return nullptr;
			mStream.get();

			auto block = parse_block();
			if (block == nullptr) throw std::runtime_error("Expected block");

			return block;
		}

		ThrowStmt* parse_throw_stmt() {
			if (mStream.eof() || mStream.peek()->type != THROW) return nullptr;
			mStream.get();

			auto expr = parse_expression();
			if (expr == nullptr) throw std::runtime_error("Expected expression");

			return CreateNode<ThrowStmt>(expr);
		}
	public:
		ast::LongBlockExpr* parse() {
			auto stmts = parse_statements(true);
			return CreateNode<LongBlockExpr>(stmts);
		}

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

using namespace orange::ast;
using namespace orange::parser;

LongBlockExpr* Parser::parse() { return mParserImpl->parse(); }
Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) { }
