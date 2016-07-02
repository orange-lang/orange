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

namespace orange { namespace parser { namespace impl {
	using namespace orange::ast;

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

				Identifier* RHS;

				switch (mStream.peek()->type) {
					case TokenType::DOT:
						mStream.get();
						RHS = parse_identifier_base();
						if (RHS == nullptr) throw std::runtime_error("Expected identifier");
						LHS = CreateNode<AccessIDExpr>(LHS, RHS);
					case TokenType::LESS_THAN:
						throw std::runtime_error("Don't know how to handle generics in full IDs");
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
				ids.insert(ids.begin(), remaining.begin(), remaining.end());

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

		EnumStmt* parse_enum();
		EnumStmt* parse_enum_base();
		std::vector<EnumValue*> parse_enum_values();
		std::vector<EnumValue*> parse_enum_values_1();
		std::vector<VarDeclExpr*> parse_opt_enum_params();

		ClassStmt* parse_class();
		ClassStmt* parse_base_class();
		std::vector<Identifier*> parse_opt_supers();
		std::vector<Identifier*> parse_super_list();
		std::vector<Identifier*> parse_super_list_1();

		ClassStmt* parse_partial_class();

		LongBlockExpr* parse_class_body();
		std::vector<Node*> parse_opt_class_stmts();
		std::vector<Node*> parse_class_stmts();
		std::vector<Node*> parse_class_stmts_1();

		Node* parse_class_stmt();

		FunctionExpr* parse_function();
		FunctionExpr* parse_base_function();
		Identifier* parse_opt_identifier();
		Identifier* parse_opt_name();
		std::vector<VarDeclExpr*> parse_opt_param_list();
		std::vector<VarDeclExpr*> parse_param_list();
		std::vector<VarDeclExpr*> parse_param_list_1();
		Type* parse_opt_func_type();
		ExternFuncStmt* parse_extern_fn();
		ExternFuncStmt* parse_base_extern();

		VarDeclExpr* parse_implicit_var();
		Type* parse_opt_type_spec();

		AggregateStmt* parse_aggregate();
		InterfaceStmt* parse_interface();

		NamespaceStmt* parse_namespace();
		BlockExpr* parse_opt_block();
		ImportStmt* parse_import();

		ExtendStmt* parse_extension();

		PropertyStmt* parse_property();
		PropertyStmt* parse_property_base();

		ExprStmt* parse_expr_statement();
		ExprStmt* parse_expr_statement_1();

		GetterStmt* parse_getter();
		SetterStmt* parse_setter();

		/*
		 * Expressions
		 */

		// TODO: this next section will probably be reworked to fit the op-precedence parser
		Expression* parse_expression();
		TernaryExpr* parse_ternary_expr();
		Expression* parse_assign_expr();
		Expression* parse_or_expr();
		Expression* parse_and_expr();
		Expression* parse_bit_or_expr();
		Expression* parse_bit_xor_expr();
		Expression* parse_bit_and_expr();
		Expression* parse_equality();
		Expression* parse_comparison();
		Expression* parse_shifts();
		Expression* parse_sums();
		Expression* parse_mult();


		Expression* parse_unary();
		Expression* parse_values();
		MemberAccessExpr* parse_dot();
		Expression* parse_primary();
		Expression* parse_value();
		Value* parse_constant_val();
		Expression* parse_control();
		Expression* parse_type_cast();

		ArrayExpr* parse_array_expression();
		std::vector<Expression*> parse_opt_arr_elements();
		std::vector<Expression*> parse_arr_elements();
		std::vector<Expression*> parse_arr_elements_1();

		ArrayAccessExpr* parse_array_access_expr();
		ArrayRangeExpr* parse_inclusive_range_expr();
		ArrayRangeExpr* parse_exclusive_range_expr();

		TupleExpr* parse_tuple_expr();
		std::vector<Expression*> parse_tuple_values();
		std::vector<Expression*> parse_tuple_values_1();
		Expression* parse_tuple_value();
		Token* parse_opt_comma();

		NamedExpr* parse_named_expr();

		IfExpr* parse_if();
		std::vector<ConditionalBlock*> parse_elif_or_else();
		ConditionalBlock* parse_else();

		Expression* parse_for_component();
		LoopStmt* parse_for_loop();
		LoopStmt* parse_foreach();
		LoopStmt* parse_while();
		LoopStmt* parse_forever();
		LoopStmt* parse_do_while();

		SwitchExpr* parse_switch();
		BlockExpr* parse_switch_block();
		std::vector<SwitchPattern*> parse_opt_switch_matches();
		std::vector<SwitchPattern*> parse_switch_matches();
		std::vector<SwitchPattern*> parse_switch_matches_1();
		SwitchPattern* parse_switch_match();
		std::vector<Expression*> parse_switch_patterns();
		std::vector<Expression*> parse_switch_patterns_1();
		Expression* parse_switch_value();
		Expression* parse_switch_pattern();

		BreakStmt* parse_break_stmt();
		ContinueStmt* parse_continue_stmt();
		YieldStmt* parse_yield_stmt();

		FunctionCallExpr* parse_fn_call();
		std::vector<Expression*> parse_opt_arg_list();
		std::vector<Expression*> parse_arg_list();
		std::vector<Expression*> parse_arg_list_1();
		Expression* parse_arg();

		Generics* parse_opt_generics();
		Generics* parse_generics();
		std::vector<Identifier*> parse_opt_generic_values();
		std::vector<Identifier*> parse_generic_values();
		std::vector<Identifier*> parse_generic_values_1();
		std::vector<Constraint*> parse_opt_constraints();
		std::vector<Constraint*> parse_constraints();
		std::vector<Constraint*> parse_constraints_1();
		Constraint* parse_constraint();
		Constraint* parse_type_constraint();

		NewExpr* parse_new();
		DeleteStmt* parse_delete();

		std::vector<Flag*> parse_flags();
		std::vector<Flag*> parse_flags_1();
		Flag* parse_flag();
		Flag* parse_virtual();
		Flag* parse_privacy();

		TryExpr* parse_try_block();
		std::vector<CatchBlock*> parse_opt_catch_blocks();
		std::vector<CatchBlock*> parse_catch_blocks();
		std::vector<CatchBlock*> parse_catch_blocks_1();
		CatchBlock* parse_catch_block();
		BlockExpr* parse_opt_finally_block();
		BlockExpr* parse_finally_block();
		ThrowStmt* parse_throw_stmt();
	public:
		ast::LongBlockExpr* parse();

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

using namespace orange::ast;
using namespace orange::parser;

LongBlockExpr* Parser::parse() { return mParserImpl->parse(); }
Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) { }

using namespace orange::parser::impl;
