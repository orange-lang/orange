//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <map>
#include <iostream>
#include <libparse/parser.h>

#include "lex_stream.h"
#include "parser-private.h"

using namespace orange::ast;
using namespace orange::parser;

static std::map<TokenType, std::string> TokenTyMap = {
	{TokenType::TOKEN_EOF, "EOF"}, {TokenType::VAL_INT, "int value"}, {TokenType::VAL_INT8, "int8 value"}, {TokenType::VAL_INT16, "int16 value"},
	{TokenType::VAL_INT32, "int32 value"}, {TokenType::VAL_INT64, "int64 value"}, {TokenType::VAL_UINT, "uint value"}, {TokenType::VAL_UINT8, "uint8 value"},
	{TokenType::VAL_UINT16, "uint16 value"}, {TokenType::VAL_UINT32, "uint32 value"}, {TokenType::VAL_UINT64, "uint64 value"}, {TokenType::VAL_FLOAT, "float value"},
	{TokenType::VAL_DOUBLE, "double value"}, {TokenType::VAL_STRING, "string value"}, {TokenType::VAL_CHAR, "char value"}, {TokenType::VAL_BOOL, "bool value"},
	{TokenType::COMMENT, "comment"}, {TokenType::FLOAT, "float"}, {TokenType::STRING, "string"}, {TokenType::NEWLINE, "newline"},
	{TokenType::SEMICOLON, ";"}, {TokenType::INT, "int"}, {TokenType::UINT, "uint"}, {TokenType::INT8, "int8"},
	{TokenType::INT16, "int16"}, {TokenType::INT32, "int32"}, {TokenType::INT64, "int64"}, {TokenType::UINT8, "uint8"},
	{TokenType::UINT16, "uint16"}, {TokenType::UINT32, "uint32"}, {TokenType::UINT64, "uint64"}, {TokenType::DOUBLE, "double"},
	{TokenType::CHAR, "char"}, {TokenType::VAR, "var"}, {TokenType::VOID, "void"}, {TokenType::IDENTIFIER, "identifier"},
	{TokenType::TEMP, "_"}, {TokenType::OPERATOR, "operator"}, {TokenType::OPEN_PAREN, "("}, {TokenType::CLOSE_PAREN, ")"},
	{TokenType::PLUS, "+"}, {TokenType::MINUS, "-"}, {TokenType::DIVIDE, "/"}, {TokenType::TIMES, "*"},
	{TokenType::REMAINDER, "%"}, {TokenType::BIT_OR, "|"}, {TokenType::BIT_AND, "&"}, {TokenType::BIT_XOR, "^"},
	{TokenType::QUESTION, "?"}, {TokenType::SHIFT_LEFT, "<<"}, {TokenType::SHIFT_RIGHT, ">>"}, {TokenType::ASSIGN, "="},
	{TokenType::EQUALS, "=="}, {TokenType::PLUS_ASSIGN, "+="}, {TokenType::MINUS_ASSIGN, "-="}, {TokenType::TIMES_ASSIGN, "*="},
	{TokenType::DIVIDE_ASSIGN, "/="}, {TokenType::REMAINDER_ASSIGN, "%="}, {TokenType::SHIFT_LEFT_ASSIGN, "<<="}, {TokenType::SHIFT_RIGHT_ASSIGN, ">>="},
	{TokenType::BIT_OR_ASSIGN, "|="}, {TokenType::BIT_AND_ASSIGN, "&="}, {TokenType::BIT_XOR_ASSIGN, "^="}, {TokenType::LESS_THAN, "<"},
	{TokenType::GREATER_THAN, ">"}, {TokenType::LEQ, "<="}, {TokenType::GEQ, ">="}, {TokenType::NEQ, "!="},
	{TokenType::AND, "&&"}, {TokenType::OR, "||"}, {TokenType::INCREMENT, "++"}, {TokenType::DECREMENT, "--"},
	{TokenType::ENUM, "enum"}, {TokenType::OPEN_CURLY, "{"}, {TokenType::CLOSE_CURLY, "}"}, {TokenType::COMMA, ","},
	{TokenType::DOT, "."}, {TokenType::CLASS, "class"}, {TokenType::PARTIAL, "partial"}, {TokenType::OPEN_BRACKET, "["},
	{TokenType::CLOSE_BRACKET, "]"}, {TokenType::EXCLUSIVE_RANGE, "..."}, {TokenType::INCLUSIVE_RANGE, ".."}, {TokenType::COLON, ":"},
	{TokenType::IN, "in"}, {TokenType::IF, "if"}, {TokenType::ELIF, "elif"}, {TokenType::ELSE, "else"},
	{TokenType::FOR, "for"}, {TokenType::FOREACH, "foreach"}, {TokenType::WHILE, "while"}, {TokenType::FOREVER, "forever"},
	{TokenType::DO, "do"}, {TokenType::SWITCH, "switch"}, {TokenType::BREAK, "break"}, {TokenType::CONTINUE, "continue"},
	{TokenType::YIELD, "yield"}, {TokenType::DEF, "def"}, {TokenType::ARROW, "->"}, {TokenType::EXTERN, "extern"},
	{TokenType::AGGREGATE, "aggregate"}, {TokenType::INTERFACE, "interface"}, {TokenType::TILDE, "~"}, {TokenType::NAMESPACE, "namespace"},
	{TokenType::IMPORT, "import"}, {TokenType::NEW, "new"}, {TokenType::DELETE, "delete"}, {TokenType::PRIVATE, "private"},
	{TokenType::PROTECTED, "protected"}, {TokenType::PUBLIC, "public"}, {TokenType::GET, "get"}, {TokenType::SET, "set"},
	{TokenType::VIRTUAL, "virtual"}, {TokenType::FINAL, "final"}, {TokenType::WHERE, "where"}, {TokenType::DATA, "data"},
	{TokenType::EXTEND, "extend"}, {TokenType::NOT, "!"}, {TokenType::CONST, "const"}, {TokenType::TRY, "try"},
	{TokenType::CATCH, "catch"}, {TokenType::FINALLY, "finally"}, {TokenType::THROW, "throw"}, {TokenType::OF, "of"},
	{TokenType::AS, "as"}, {TokenType::PROPERTY, "property"}, {TokenType::THIS, "this"}, {TokenType::BOOL, "bool"}
};

namespace orange { namespace parser { namespace impl {
	using namespace orange::ast;

	class Parser {
	private:
		LexStream mStream;

	public:
		// Error handling
		void Expected(std::string expected) {
			auto tok = GetNextConcreteToken();
			auto str = tok->value;
			if (str == "" || str == "\n") str = TokenTyMap[tok->type];

			std::cerr << "Expected " << expected << ", got " << str << std::endl;
		}

		void Expected(std::string expected, Token* tok) {
			auto str = tok->value;
			if (str == "" || str == "\n") str = TokenTyMap[tok->type];

			std::cerr << "Expected " << expected << ", got " << str << std::endl;
		}

		bool Expect(TokenType ty, Token* tok) {
			if (tok->type != ty) Expected(TokenTyMap[ty], tok);
			return tok->type == ty;
		}

		bool Expect(TokenType ty) {
			auto next = GetNextConcreteToken();
			if (next->type != ty) Expected(TokenTyMap[ty], next);
			return next->type == ty;
		}

		// Consume tokens until EOF, semicolon, or newline.
		// If any token we ran into was a {, continue consuming tokens until }.
		void PanicRecovery() {
			auto next = mStream.get();
			int braces = 0;

			while (next->type != TOKEN_EOF && next->type != SEMICOLON && next->type != NEWLINE) {
				if      (next->type ==  OPEN_CURLY) braces++;
				else if (next->type == CLOSE_CURLY) braces--;

				next = mStream.get();
			}

			while (braces > 0 && next->type != TOKEN_EOF) {
				if      (next->type ==  OPEN_CURLY) braces++;
				else if (next->type == CLOSE_CURLY) braces--;

				next = mStream.get();
			}

			// Even if we found a mis-matched brace, we still want to recover from the situation.
			// The closest recovery is when there is no mismatched braces and we hit a ;, newline, or EOF
			if (braces > 0) {
				Expected("}");
				PanicRecovery();
			}
		}

		/// Gets the next "concrete" (e.g., non-comment, non-newline) token
		Token* PeekNextConcreteToken() {
			Token* next = nullptr;

			for (int lookahead = 1; next == nullptr; lookahead++) {
				auto tokens = mStream.peek(lookahead);
				if (tokens.back()->type != COMMENT && tokens.back()->type != NEWLINE) next = tokens.back();
			}

			return next;
		}

		/// Peeks the next "concrete" (e.g., non-comment, non-newline) token
		Token* GetNextConcreteToken() {
			bool foundToken = false;

			int lookahead = 0;
			while (!foundToken) {
				auto tokens = mStream.peek(++lookahead);
				if (tokens.back()->type != COMMENT && tokens.back()->type != NEWLINE) foundToken = true;
			}

			return mStream.get(lookahead).back();
		}

		std::vector<Node*> ParseStatements() {
			auto statements = std::vector<Node*>();
			auto next = PeekNextConcreteToken();

			while (next->type != CLOSE_CURLY && next->type != TOKEN_EOF) {
				auto stmt = ParseStatement();

				if (stmt != nullptr) {
					statements.push_back(stmt);
				} else {
					Expected("statement");
					PanicRecovery();
				}

				next = PeekNextConcreteToken();
			}

			return statements;
		}

		Node* ParseStatement() {
			switch (PeekNextConcreteToken()->type) {
				case OPEN_CURLY:
					return ParseLongBlock();
				case VAL_BOOL:   case VAL_INT:    case VAL_INT8:
				case VAL_INT16:  case VAL_INT32:  case VAL_INT64:
				case VAL_UINT:   case VAL_UINT8:  case VAL_UINT16:
				case VAL_UINT32: case VAL_UINT64: case VAL_FLOAT:
				case VAL_DOUBLE: case VAL_CHAR:   case VAL_STRING:
					return ParseExpression();
				case TokenType::VAR:
					return ParseVarDecl();
				default: break;
			}

			return nullptr;
		}

		VarDeclExpr* ParseVarDecl() {
			if (!Expect(TokenType::VAR)) return nullptr;

			// Allow single identifier or (
			std::vector<Identifier*> ids;
			std::vector<Type*> tys;
			Expression* value = nullptr;

			auto next = GetNextConcreteToken();
			if (next->type == IDENTIFIER) {
				ids.push_back(CreateNode<NamedIDExpr>(next->value));
			} else if (next->type == OPEN_PAREN) {
				next = GetNextConcreteToken();
				if (!Expect(IDENTIFIER, next)) return nullptr;

				ids.push_back(CreateNode<NamedIDExpr>(next->value));

				next = GetNextConcreteToken();

				while (next->type == COMMA) {
					next = GetNextConcreteToken();
					if (!Expect(IDENTIFIER, next)) return nullptr;

					ids.push_back(CreateNode<NamedIDExpr>(next->value));

					next = GetNextConcreteToken();
				}

				if (!Expect(CLOSE_PAREN, next)) return nullptr;
			} else {
				Expected("identifier", next);
				return nullptr;
			}

			if (PeekNextConcreteToken()->type == COLON) {
				GetNextConcreteToken();
				auto ty = ParseType();

				if (ty == nullptr) {
					Expected("type");
					return nullptr;
				}

				tys.push_back(ty);

				while (PeekNextConcreteToken()->type == COMMA) {
					GetNextConcreteToken();

					auto ty = ParseType();

					if (ty == nullptr) {
						Expected("type");
						return nullptr;
					}
				}
			}

			if (PeekNextConcreteToken()->type == ASSIGN) {
				GetNextConcreteToken();
				value = ParseExpression();

				if (value == nullptr) {
					Expected("expression");
					return nullptr;
				}
			}

			return CreateNode<VarDeclExpr>(ids, tys, value);
		}

		Type* ParseType() {
			return nullptr;
		}

		/// Binary expression _or_ unary expression
		Expression* ParseExpression() {
			return ParseUnary();
		}

		/// Unary expression _or_ operation
		Expression* ParseUnary() {
			return ParseOperation();
		}

		/// Operation _or_ primary
		Expression* ParseOperation() {
			return ParsePrimary();
		}

		Expression* ParsePrimary() {
			auto token = PeekNextConcreteToken();
			switch (token->type) {
				case VAL_BOOL:   case VAL_INT:    case VAL_INT8:
				case VAL_INT16:  case VAL_INT32:  case VAL_INT64:
				case VAL_UINT:   case VAL_UINT8:  case VAL_UINT16:
				case VAL_UINT32: case VAL_UINT64: case VAL_FLOAT:
				case VAL_DOUBLE: case VAL_CHAR:   case VAL_STRING:
					return ParseConstantValue();
				default:
					Expected("value", token);
					return nullptr;
			}

		}

		Value* ParseConstantValue() {
			auto token = GetNextConcreteToken();

			if (IsIntToken(token)) {
				auto value = ToInt(token);
				return CreateNode<IntValue>(value, TypeFromToken(token));
			} else if (IsUIntToken(token)) {
				auto value = ToUInt(token);
				return CreateNode<UIntValue>(value, TypeFromToken(token));
			} else if (token->type == VAL_FLOAT) {
				auto value = ToFloat(token);
				return CreateNode<FloatValue>(value);
			} else if (token->type == VAL_DOUBLE) {
				auto value = ToDouble(token);
				return CreateNode<DoubleValue>(value);
			} else if (token->type == VAL_CHAR) {
				return CreateNode<CharValue>(token->value[0]);
			} else if (token->type == VAL_STRING) {
				return CreateNode<StringValue>(token->value);
			} else if (token->type == VAL_BOOL) {
				return CreateNode<BoolValue>(ToBool(token));
			} else {
				Expected("value", token);
				return nullptr;
			}
		}

		LongBlockExpr* ParseLongBlock() {
			if (!Expect(OPEN_CURLY)) return nullptr;
			auto stmts = ParseStatements();
			if (!Expect(CLOSE_CURLY)) return nullptr;

			return CreateNode<LongBlockExpr>(stmts);
		}

		LongBlockExpr* parse() {
			auto ast = CreateNode<LongBlockExpr>();

			if (mStream.eof() || PeekNextConcreteToken()->type == TOKEN_EOF) return ast;

			ast->statements = ParseStatements();
			return ast;
		}

		Parser(std::istream& stream) : mStream(stream) { }
	};
}}}

LongBlockExpr* Parser::parse() {
	return mParserImpl->parse();
}

Parser::Parser(std::istream& stream) : mParserImpl(new impl::Parser(stream)) { }
