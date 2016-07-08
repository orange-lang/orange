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

	class Parser {
	private:
		LexStream mStream;
	protected:
		bool isTerm(Token* tok);
		bool checkNext(TokenType ty);

		std::vector<Node *> parse_opt_statements();
		std::vector<Node *> parse_statements(bool allow_eps = false);
		Token* parse_term();
		LongBlockExpr* parse_long_block();
		ShortBlockExpr* parse_short_block();
		BlockExpr* parse_block();

		/*
		 * Types
		 */

		Type* parse_type();
		Type* parse_basic_type();
		Type* parse_complex_type();
		Type* parse_complex_type_base();
		Type* parse_tuple_or_func_type();
		Type* parse_base_id_type();
		Type* parse_operator_id_ty();

		/*
		 * Identifier
		 */

		Identifier* parse_identifier();
		Generics* parse_opt_generic_spec();
		Identifier* parse_identifier_base();
		Identifier* parse_full_identifier();

		/*
		 * Statements
		 */

		Node* parse_statement(bool getExprStmt = false);

		VarDeclExpr* parse_var_decl();

		Flag* parse_opt_const();

		std::vector<Identifier*> parse_identifiers();
		std::vector<Identifier*> parse_identifier_list();

		std::vector<Type*> parse_opt_type_spec_list();

		Expression* parse_opt_value();

		EnumStmt* parse_enum();
		EnumStmt* parse_enum_base();
		std::vector<EnumValue*> parse_enum_values();
		EnumValue* parse_enum_value();
		std::vector<VarDeclExpr*> parse_opt_enum_params();

		ClassStmt* parse_class();
		ClassStmt* parse_base_class();
		std::vector<Identifier*> parse_opt_supers();
		ClassStmt* parse_partial_class();
		LongBlockExpr* parse_class_body();
		std::vector<Node*> parse_class_stmts();
		Node* parse_class_stmt();
		VarDeclExpr* parse_class_member();

		FunctionExpr* parse_function();
		FunctionExpr* parse_base_function();
		std::vector<VarDeclExpr*> parse_param_list();
		Type* parse_opt_func_type();

		ExternFuncStmt* parse_extern_fn();
		ExternFuncStmt* parse_base_extern();

		VarDeclExpr* parse_implicit_var();

		Type* parse_opt_type_spec();

		AggregateStmt* parse_aggregate();
		InterfaceStmt* parse_interface();
		NamespaceStmt* parse_namespace();
		ImportStmt* parse_import();
		ExtendStmt* parse_extension();

		PropertyStmt* parse_property();
		PropertyStmt* parse_property_base();
		Node* parse_expr_statement();
		GetterStmt* parse_getter();
		SetterStmt* parse_setter();

		/*
		 * Expressions
		 */

		Expression* parse_expression();
		Expression* parse_expression_1(Expression* LHS, int min_precedence);

		Expression* parse_unary();
		Expression* parse_values();
		Expression* parse_primary();
		Expression* parse_value();

		Value* parse_constant_val();

		Expression* parse_this();
		Expression* parse_control();

		NewExpr* parse_new();

		ArrayExpr* parse_array_expression();

		ArrayRangeExpr* parse_inclusive_range_expr();
		ArrayRangeExpr* parse_exclusive_range_expr();

		/// Also parses (expression) as just an expression. A trailing comma
		/// is required to make it a tuple.
		Expression* parse_tuple_expr();
		Expression* parse_tuple_value();

		NamedExpr* parse_named_expr();

		IfExpr* parse_if();
		std::vector<ConditionalBlock*> parse_elif_or_else();
		ConditionalBlock* parse_else();

		Expression* parse_for_component();
		LoopStmt* parse_for_loop();
		ForeachStmt* parse_foreach();
		LoopStmt* parse_while();
		LoopStmt* parse_forever();
		LoopStmt* parse_do_while();

		SwitchExpr* parse_switch();
		std::vector<SwitchPattern*> parse_switch_block();
		std::vector<SwitchPattern*> parse_switch_matches();
		SwitchPattern* parse_switch_match();
		std::vector<Expression*> parse_switch_patterns();
		Expression* parse_switch_pattern();
		BlockExpr* parse_switch_value();

		BreakStmt* parse_break_stmt();
		ContinueStmt* parse_continue_stmt();
		YieldStmt* parse_yield_stmt();

		std::vector<Expression*> parse_arg_list();
		Expression* parse_arg();

		Generics* parse_generics();
		std::vector<Identifier*> parse_generic_values();
		std::vector<Constraint*> parse_opt_constraints();
		std::vector<Constraint*> parse_constraints();
		Constraint* parse_constraint();
		Constraint* parse_type_constraint(Identifier* id);

		DeleteStmt* parse_delete();

		std::vector<Flag*> parse_flags();
		Flag* parse_flag();
		Flag* parse_virtual();
		Flag* parse_privacy();
		Flag* parse_partial();

		TryExpr* parse_try_block();
		std::vector<CatchBlock*> parse_catch_blocks();
		BlockExpr* parse_finally_block();
		ThrowStmt* parse_throw_stmt();
	public:
		ast::LongBlockExpr* parse();

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

