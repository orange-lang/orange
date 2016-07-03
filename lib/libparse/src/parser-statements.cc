//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>

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


