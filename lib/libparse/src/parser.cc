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
			if (str == "" || str == "\n") str = TokenDescriptionMap[tok->type];

			std::cerr << "Expected " << expected << ", got " << str << std::endl;
		}

		void Expected(std::string expected, Token* tok) {
			auto str = tok->value;
			if (str == "" || str == "\n") str = TokenDescriptionMap[tok->type];

			std::cerr << "Expected " << expected << ", got " << str << std::endl;
		}

		bool Expect(TokenType ty, Token* tok) {
			if (tok->type != ty) Expected(TokenDescriptionMap[ty], tok);
			return tok->type == ty;
		}

		bool Expect(TokenType ty) {
			auto next = GetNextConcreteToken();
			if (next->type != ty) Expected(TokenDescriptionMap[ty], next);
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

					tys.push_back(ty);
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

		/// Parse type _or_ basic type
		Type* ParseType() {
			Type* base = ParseBasicType();

			auto lookahead = mStream.peek();
			while (lookahead->type == OPEN_BRACKET || lookahead->type == TIMES || lookahead->type == BIT_AND ||
				   lookahead->type == AND)
			{
				mStream.get();

				if (lookahead->type == OPEN_BRACKET) {
					auto value = ParseExpression();
					if (!Expect(CLOSE_BRACKET)) return nullptr;
					base = new ArrayType(base, value);
				} else if (lookahead->type == TIMES) {
					base = new PointerType(base);
				} else if (lookahead->type == BIT_AND) {
					base = new ReferenceType(base);
				} else if (lookahead->type == AND) {
					base = new ReferenceType(new ReferenceType(base));
				}

				lookahead = mStream.peek();
			}

			return base;
		}

		Type* ParseBasicType() {
			auto ty = GetNextConcreteToken();

			if      (ty->type == INT)    { return new BuiltinType(BuiltinTypeKind::INT); }
			else if (ty->type == INT8)   { return new BuiltinType(BuiltinTypeKind::INT8); }
			else if (ty->type == INT16)  { return new BuiltinType(BuiltinTypeKind::INT16); }
			else if (ty->type == INT32)  { return new BuiltinType(BuiltinTypeKind::INT32); }
			else if (ty->type == INT64)  { return new BuiltinType(BuiltinTypeKind::INT64); }
			else if (ty->type == UINT)   { return new BuiltinType(BuiltinTypeKind::UINT); }
			else if (ty->type == UINT8)  { return new BuiltinType(BuiltinTypeKind::UINT8); }
			else if (ty->type == UINT16) { return new BuiltinType(BuiltinTypeKind::UINT16); }
			else if (ty->type == UINT32) { return new BuiltinType(BuiltinTypeKind::UINT32); }
			else if (ty->type == UINT64) { return new BuiltinType(BuiltinTypeKind::UINT64); }
			else if (ty->type == FLOAT)  { return new BuiltinType(BuiltinTypeKind::FLOAT); }
			else if (ty->type == DOUBLE) { return new BuiltinType(BuiltinTypeKind::DOUBLE); }
			else if (ty->type == VAR)    { return new BuiltinType(BuiltinTypeKind::VAR); }
			else if (ty->type == VOID)   { return new BuiltinType(BuiltinTypeKind::VOID); }
			else if (ty->type == CHAR)   { return new BuiltinType(BuiltinTypeKind::CHAR); }

			if (ty->type == IDENTIFIER) {
				// Identifier type
				Type* LHS = new IdentifierType(CreateNode<ReferenceIDExpr>(ty->value));

				while (mStream.peek()->type == DOT) {
					mStream.get();

					auto next = mStream.get();
					if (!Expect(IDENTIFIER, next)) return nullptr;

					LHS = new AccessType(LHS, new IdentifierType(CreateNode<ReferenceIDExpr>(next->value)));
				}

				return LHS;
			} else if (ty->type == OPEN_PAREN) {
				// Function or tuple
				std::vector<Type*> tys;

				auto member = ParseType();
				if (member == nullptr) {
					Expected("type");
					return nullptr;
				}

				tys.push_back(member);

				unsigned long commas = 0;

				while (PeekNextConcreteToken()->type == COMMA) {
					commas++;
					GetNextConcreteToken();

					// Allow trailing comma before )
					if (PeekNextConcreteToken()->type == CLOSE_PAREN) break;

					member = ParseType();
					if (member == nullptr) {
						Expected("type");
						return nullptr;
					}

					tys.push_back(member);
				}

				if (!Expect(CLOSE_PAREN)) return nullptr;

				// if there wasn't a trailing comma, accept ->
				if (commas < tys.size() && PeekNextConcreteToken()->type == ARROW) {
					GetNextConcreteToken();

					auto ret = ParseType();
					if (ret == nullptr) {
						Expected("type");
						return nullptr;
					}

					return new FunctionType(tys, ret);
				}

				return commas > 0 ? new TupleType(tys) : tys.front();
			}

			Expected("type", ty);
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
