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

			while (next->type == SEMICOLON) {
				GetNextConcreteToken();
				next = PeekNextConcreteToken();
			}

			while (next->type != CLOSE_CURLY && next->type != TOKEN_EOF) {
				auto stmt = ParseStatement();

				if (stmt != nullptr) {
					statements.push_back(stmt);
				} else {
					Expected("statement");
					PanicRecovery();
				}

				next = PeekNextConcreteToken();

				while (next->type == SEMICOLON) {
					GetNextConcreteToken();
					next = PeekNextConcreteToken();
				}
			}

			return statements;
		}

		Node* ParseStatement() {
			auto flags = ParseFlags();

			Node* node = nullptr;

			switch (PeekNextConcreteToken()->type) {
				case TokenType::VAR:
					node = ParseVarDecl();
					break;
				case DEF:
					node = ParseFunction();
					break;
				case NAMESPACE:
					node = ParseNamespace();
					break;
				default: break;
			}

			// Parse remaining statements that don't support flags
			if (flags.size() == 0 && node == nullptr) {
				switch (PeekNextConcreteToken()->type) {
					case OPEN_CURLY:
						node = ParseLongBlock();
						break;
					case TokenType::TIMES: case TokenType::BIT_AND:
					case TokenType::TILDE: case TokenType::NOT:
					case TokenType::MINUS: case TokenType::INCREMENT:
					case TokenType::DECREMENT:
					case VAL_BOOL:   case VAL_INT:    case VAL_INT8:
					case VAL_INT16:  case VAL_INT32:  case VAL_INT64:
					case VAL_UINT:   case VAL_UINT8:  case VAL_UINT16:
					case VAL_UINT32: case VAL_UINT64: case VAL_FLOAT:
					case VAL_DOUBLE: case VAL_CHAR:   case VAL_STRING:
					case THIS:       case IDENTIFIER:
						node = ParseExpression();
						break;
					default: break;
				}
			}

			if (node != nullptr) {
				node->flags.insert(node->flags.end(), flags.begin(), flags.end());
			}

			return node;
		}

		bool IsFlag(Token* tok) {
			switch (tok->type) {
				case TokenType::PRIVATE: case TokenType::PROTECTED: case TokenType::PUBLIC:
				case TokenType::VIRTUAL: case TokenType::FINAL:     case TokenType::CONST:
				case TokenType::PARTIAL:
					return true;
				default:
					return false;
			}
		}

		std::vector<Flag*> ParseFlags() {
			std::vector<Flag*> flags;

			while (IsFlag(PeekNextConcreteToken())) {
				auto flag = GetNextConcreteToken();

				if      (flag->type == TokenType::PRIVATE)   flags.push_back(new PrivacyFlag(PrivacyLevel::PRIVATE));
				else if (flag->type == TokenType::PROTECTED) flags.push_back(new PrivacyFlag(PrivacyLevel::PROTECTED));
				else if (flag->type == TokenType::PUBLIC)    flags.push_back(new PrivacyFlag(PrivacyLevel::PUBLIC));
				else if (flag->type == TokenType::VIRTUAL)   flags.push_back(new VirtualFlag());
				else if (flag->type == TokenType::FINAL)     flags.push_back(new FinalFlag());
				else if (flag->type == TokenType::CONST)     flags.push_back(new ConstFlag());
				else if (flag->type == TokenType::PARTIAL)   flags.push_back(new PartialFlag());
				else                                         { Expected("flag"); break; }
			}

			return flags;
		}

		FunctionExpr* ParseFunction() {
			if (!Expect(DEF)) return nullptr;

			Identifier* id = nullptr;
			std::vector<VarDeclExpr*> params;
			Type* retType = nullptr;

			if (PeekNextConcreteToken()->type == IDENTIFIER) {
				auto token = GetNextConcreteToken();
                id = CreateNode<NamedIDExpr>(token->value);
			}

			if (!Expect(OPEN_PAREN)) return nullptr;

			if (PeekNextConcreteToken()->type == IDENTIFIER) {
				params = ParseParameterList();
			}

			if (!Expect(CLOSE_PAREN)) return nullptr;

			if (PeekNextConcreteToken()->type == ARROW) {
				auto token = GetNextConcreteToken();
				retType = ParseType();

				if (retType == nullptr) {
					Expected("type");
					return nullptr;
				}
			}

			auto body = ParseBlock();
			if (body == nullptr) {
				Expected("block");
				return nullptr;
			}

			return new FunctionExpr(id, nullptr, params, retType, body);
		}

		std::vector<VarDeclExpr*> ParseParameterList() {
			std::vector<VarDeclExpr*> params;

			auto param = ParseImplicitParameter();
			if (param == nullptr) { Expected("parameter"); return std::vector<VarDeclExpr*>(); }
			params.push_back(param);

			while (PeekNextConcreteToken()->type == COMMA) {
				GetNextConcreteToken();

				param = ParseImplicitParameter();
				if (param == nullptr) { Expected("parameter"); return std::vector<VarDeclExpr*>(); }
				params.push_back(param);
			}

			return params;
		}

		VarDeclExpr* ParseImplicitParameter() {
			auto id = GetNextConcreteToken();
			std::vector<Type*> types;
			Expression* value = nullptr;

			if (!Expect(IDENTIFIER, id)) return nullptr;

			if (PeekNextConcreteToken()->type == COLON) {
				GetNextConcreteToken();
				auto ty = ParseType();

				if (ty == nullptr) { Expected("type"); return nullptr; }

				types.push_back(ty);
			}

			if (PeekNextConcreteToken()->type == ASSIGN) {
				GetNextConcreteToken();
				value = ParseExpression();

				if (value == nullptr) { Expected("expression"); return nullptr; }
			}

			return CreateNode<VarDeclExpr>(
				std::vector<Identifier*>({ CreateNode<NamedIDExpr>(id->value) }),
				types, value
			);
		}

		NamespaceStmt* ParseNamespace() {
			if (!Expect(NAMESPACE)) return nullptr;

			auto id = ParseLongID();
			if (id == nullptr) {
				Expected("identifier");
				return nullptr;
			}

			LongBlockExpr* body = nullptr;

			if (PeekNextConcreteToken()->type == OPEN_CURLY) {
				body = ParseLongBlock();
			}

			return CreateNode<NamespaceStmt>(id, body);
		}

		Identifier* ParseLongID() {
			auto next = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, next)) return nullptr;

			Identifier* base = CreateNode<NamedIDExpr>(next->value);

			while (mStream.peek()->type == DOT) {
				mStream.get();

				next = mStream.get();
				if (!Expect(IDENTIFIER, next)) return nullptr;

				base = CreateNode<AccessIDExpr>(base, CreateNode<NamedIDExpr>(next->value));
			}

			return base;
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
		/// new/delete is also parsed here
		Expression* ParseUnary() {
			auto token = PeekNextConcreteToken();
			Expression* inner = nullptr;

			switch (token->type) {
				case TokenType::INCREMENT: case TokenType::DECREMENT: case TokenType::MINUS:
				case TokenType::NOT:       case TokenType::TILDE:     case TokenType::TIMES:
				case TokenType::BIT_AND:
					GetNextConcreteToken();
					inner = ParseUnaryInner();
					if (inner == nullptr) { Expected("Expression"); return nullptr; }
					return CreateNode<UnaryExpr>(GetUnaryOp(token->type), UnaryOrder::PREFIX, inner);
			}

			return ParseOperation();
		}

		/// Equivalent to parse unary, but only looks at the next token, not skipping over \n and ;
		/// Only parses unary operators, unlike ParseUnary, which does new/delete.
		Expression* ParseUnaryInner() {
			auto token = mStream.peek();
			Expression* inner = nullptr;

			switch (token->type) {
				case TokenType::INCREMENT: case TokenType::DECREMENT: case TokenType::MINUS:
				case TokenType::NOT:       case TokenType::TILDE:     case TokenType::TIMES:
				case TokenType::BIT_AND:
					mStream.get();
					inner = ParseUnaryInner();
					if (inner == nullptr) { Expected("Expression"); return nullptr; }
					return CreateNode<UnaryExpr>(GetUnaryOp(token->type), UnaryOrder::PREFIX, inner);
			}

			return ParseOperation();
		}

		/// Operation _or_ primary
		/// The operations are: function call, array access, member access, and postfix unary operations
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
				case IDENTIFIER:
					return CreateNode<ReferenceIDExpr>(GetNextConcreteToken()->value);
				case THIS:
					GetNextConcreteToken();
					return CreateNode<ThisID>();
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

		BlockExpr* ParseBlock() {
			// We'll allow open curlies on any line, but we'll expect short blocks to be
			// defined on the same line (at least the colon, it's valid for the expression to be
			// on a separate line.)
			if (PeekNextConcreteToken()->type == OPEN_CURLY) {
				return ParseLongBlock();
			} else if (mStream.peek()->type == COLON) {
				return ParseShortBlock();
			} else {
				Expected("block");
				return nullptr;
			}
		}

		LongBlockExpr* ParseLongBlock() {
			if (!Expect(OPEN_CURLY)) return nullptr;
			auto stmts = ParseStatements();
			if (!Expect(CLOSE_CURLY)) return nullptr;

			return CreateNode<LongBlockExpr>(stmts);
		}

		ShortBlockExpr* ParseShortBlock() {
			if (!Expect(COLON)) return nullptr;
			Expression* expr = ParseExpression();
			Node* stmt = expr;
			if (stmt == nullptr) {
				Expected("statement");
				return nullptr;
			}

			if (mStream.peek()->type == SEMICOLON) {
				mStream.get();
				stmt = CreateNode<ExprStmt>(expr);
			}

			return CreateNode<ShortBlockExpr>(stmt);
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
