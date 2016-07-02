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
	using namespace orange::ast;

	class Parser {
	private:

		LexStream mStream;

		std::vector<Node *> parse_opt_statements();
		std::vector<Node *> parse_statements();
		std::vector<Node *> parse_statements_1();
		Token* parse_term();

		LongBlockExpr* parse_long_block();
		ShortBlockExpr* parse_short_block();
		BlockExpr* parse_block();

		/*
		 * Types
		 */

		/* TODO: array, pointers, and refs are left recursive, need special code */
		Type* parse_type();
		Type* parse_array_type();
		Type* parse_tuple_type();
		Type* parse_func_type();
		Type* parse_pointer_type();
		Type* parse_ref_type();

		std::vector<Type*> parse_types();
		std::vector<Type*> parse_types_1();
		std::vector<Type*> parse_types_2();

		std::vector<Type*> parse_opt_type_list();
		std::vector<Type*> parse_type_list();
		std::vector<Type*> parse_type_list_1();

		Identifier* parse_identifier();
		Identifier* parse_named_id();

		Generics* parse_opt_generic_spec();
		Generics* parse_generic_spec();
		Identifier* parse_id_types();
		Identifier* parse_full_id();
		Identifier* parse_full_id_1();
		Identifier* parse_operator_id();
		Identifier* parse_dtor_id();

		/*
		 * Statements
		 */
		Node* parse_statement();

		VarDeclExpr* parse_var_decl();
		Flag* parse_opt_const();

		std::vector<Identifier*> parse_identifiers();
		std::vector<Identifier*> parse_identifier_list();
		std::vector<Identifier*> parse_identifier_list_1();

		std::vector<Type*> parse_opt_type_spec_list();
		Expression* parse_opt_value();

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

		ExtendStmt* parse_opt_extension();

		PropertyStmt* parse_property();
		PropertyStmt* parse_property_base();

		// TODO: make AST node for this, probably don't need the _1 version
		Statement* parse_expr_statement();
		Statement* parse_expr_statement_1();

		GetterStmt* parse_getter();
		SetterStmt* parse_setter();

		/*
		 * Expressions
		 */

		/// TODO: this next section will probably be reworked to fit the op-precedence parser
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
