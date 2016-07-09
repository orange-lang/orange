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

		auto RHS = parse_unary();
		if (RHS == nullptr) throw std::runtime_error("Expected expression");

		next = mStream.peek();

		while ((GetAssociativity(next->type) == LEFT &&
		        GetOperatorPrecedence(next->type) > GetOperatorPrecedence(op)) ||
		       (GetAssociativity(next->type) == RIGHT &&
		        GetOperatorPrecedence(next->type) == GetOperatorPrecedence(op))) {
			RHS = parse_expression_1(RHS, GetOperatorPrecedence(next->type));
			next = mStream.peek();
		}

		LHS = CreateNode<BinOpExpr>(LHS, GetBinOp(op), RHS);
	}

	if (next->type == QUESTION) {
		mStream.get();
		auto trueValue = parse_expression();

		if (mStream.get()->type != COLON)
			throw std::runtime_error("Expected :");

		auto falseValue = parse_expression();

		LHS = CreateNode<TernaryExpr>(LHS, trueValue, falseValue);
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

			auto id = parse_identifier(false);
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

	if (mStream.peek()->type == IDENTIFIER) {
		return CreateNode<ReferenceIDExpr>(mStream.get()->value);
	}

	if (mStream.peek()->type == TEMP) {
		mStream.get();
		return CreateNode<TempIDExpr>();
	}

	return nullptr;
}

Value* impl::Parser::parse_constant_val() {
	auto lookahead = mStream.peek();

	if (IsIntToken(lookahead)) {
		auto tok = mStream.get();
		auto value = ToInt(tok);
		return CreateNode<IntValue>(value, TypeFromToken(tok));
	} else if (IsUIntToken(lookahead)) {
		auto tok = mStream.get();
		auto value = ToUInt(tok);
		return CreateNode<UIntValue>(value, TypeFromToken(tok));
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
	} else if (lookahead->type == VAL_BOOL) {
		return CreateNode<BoolValue>(ToBool(mStream.get()));
	}

	return nullptr;
}

Expression* impl::Parser::parse_this() {
	if (mStream.peek()->type != THIS) return nullptr;
	mStream.get();
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

	auto full_id = parse_full_identifier(false);
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

	if (mStream.peek()->type != CLOSE_BRACKET) {
		if (mStream.peek()->type == EXCLUSIVE_RANGE || mStream.peek()->type == INCLUSIVE_RANGE) {
			mStream.seek(pos);
			return nullptr;
		}

		throw std::runtime_error("Expected ]");
	}

	mStream.get();
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
	exprs.push_back(expr);

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

	while (isTerm(mStream.peek())) parse_term();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	auto blocks = parse_elif_or_else();
	blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

	return CreateNode<IfExpr>(blocks);
}

std::vector<ConditionalBlock*> impl::Parser::parse_elif_or_else() {
	std::vector<ConditionalBlock*> blocks;
	auto pos = mStream.tell();

	while (isTerm(mStream.peek())) parse_term();

	if (mStream.peek()->type != ELIF) {
		auto elseBlock = parse_else();
		if (elseBlock != nullptr) blocks.push_back(elseBlock);
		else mStream.seek(pos);
		return blocks;
	}

	mStream.get();

	if (mStream.get()->type != OPEN_PAREN)
		throw std::runtime_error("Expected (");

	auto expr = parse_expression();
	if (expr == nullptr) throw std::runtime_error("Expected expression");

	if (mStream.get()->type != CLOSE_PAREN)
		throw std::runtime_error("Expected )");

	while (isTerm(mStream.peek())) parse_term();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	blocks = parse_elif_or_else();
	blocks.insert(blocks.begin(), CreateNode<ConditionalBlock>(expr, block));

	return blocks;
}

ConditionalBlock* impl::Parser::parse_else() {
	auto pos = mStream.tell();

	while (isTerm(mStream.peek())) parse_term();

	if (mStream.peek()->type != ELSE) {
		mStream.seek(pos);
		return nullptr;
	}

	mStream.get();

	while (isTerm(mStream.peek())) parse_term();

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

	auto matches = parse_switch_matches();

	if (mStream.get()->type != CLOSE_CURLY)
		throw std::runtime_error("Expected }");

	return matches;
}

std::vector<SwitchPattern*> impl::Parser::parse_switch_matches() {
	std::vector<SwitchPattern*> matches;

	while (isTerm(mStream.peek())) parse_term();

	auto match = parse_switch_match();
	if (match == nullptr) return matches;
	matches.push_back(match);

	while (mStream.peek()->type == COMMA) {
		mStream.get();

		while (isTerm(mStream.peek())) parse_term();

		match = parse_switch_match();
		if (match == nullptr) throw std::runtime_error("Expected switch pattern");
		matches.push_back(match);
	}

	while (isTerm(mStream.peek())) parse_term();

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

	auto id = parse_identifier(false);
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

	auto base = parse_identifier(false);
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

	while (!mStream.eof()) {
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

	while (isTerm(mStream.peek())) parse_term();

	auto block = parse_block();
	if (block == nullptr) throw std::runtime_error("Expected block");

	auto catches = parse_catch_blocks();
	auto finally = parse_finally_block();

	return CreateNode<TryExpr>(block, catches, finally);
}

std::vector<CatchBlock*> impl::Parser::parse_catch_blocks() {
	std::vector<CatchBlock*> catches;
	auto pos = mStream.tell();

	while (isTerm(mStream.peek())) parse_term();

	if (mStream.peek()->type != CATCH) {
		mStream.seek(pos);
		return catches;
	}

	while (mStream.peek()->type == CATCH) {
		if (mStream.peek()->type != CATCH) return catches;
		mStream.get();

		if (mStream.get()->type != OPEN_PAREN)
			throw std::runtime_error("Expected (");

		auto exception = parse_var_decl();
		if (exception == nullptr) throw std::runtime_error("Expected expression");

		if (mStream.get()->type != CLOSE_PAREN)
			throw std::runtime_error("Expected )");

		while (isTerm(mStream.peek())) parse_term();

		auto block = parse_block();
		if (block == nullptr) throw std::runtime_error("Expected block");

		auto catch_block = CreateNode<CatchBlock>(exception, block);
		catches.push_back(catch_block);

		pos = mStream.tell();

		while (isTerm(mStream.peek())) parse_term();

		if (mStream.peek()->type != CATCH) {
			mStream.seek(pos);
			break;
		}
	}

	return catches;
}

BlockExpr* impl::Parser::parse_finally_block() {
	auto pos = mStream.tell();

	while (isTerm(mStream.peek())) parse_term();

	if (mStream.peek()->type != FINALLY) {
		mStream.seek(pos);
		return nullptr;
	}

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

	if (mStream.eof() == false) {
		throw std::runtime_error("Failed to parse the entire file");
	}

	return CreateNode<LongBlockExpr>(stmts);
}
