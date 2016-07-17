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

		bool IsBinOpToken(Token* tok) {
			switch (tok->type) {
				case TokenType::PLUS: case TokenType::MINUS: case TokenType::DIVIDE:
				case TokenType::TIMES: case TokenType::REMAINDER: case TokenType::BIT_OR:
				case TokenType::BIT_AND: case TokenType::BIT_XOR: case TokenType::SHIFT_LEFT:
				case TokenType::SHIFT_RIGHT: case TokenType::ASSIGN: case TokenType::EQUALS:
				case TokenType::PLUS_ASSIGN: case TokenType::MINUS_ASSIGN: case TokenType::TIMES_ASSIGN:
				case TokenType::DIVIDE_ASSIGN: case TokenType::REMAINDER_ASSIGN: case TokenType::SHIFT_LEFT_ASSIGN:
				case TokenType::SHIFT_RIGHT_ASSIGN: case TokenType::BIT_OR_ASSIGN: case TokenType::BIT_AND_ASSIGN:
				case TokenType::BIT_XOR_ASSIGN: case TokenType::LESS_THAN: case TokenType::GREATER_THAN:
				case TokenType::LEQ: case TokenType::GEQ: case TokenType::NEQ:
				case TokenType::AND: case TokenType::OR:
					return true;
				default: return false;
			}
		}

		bool IsExpressionToken(Token* tok) {
			switch (tok->type) {
				case TokenType::TIMES: case TokenType::BIT_AND:
				case TokenType::TILDE: case TokenType::NOT:
				case TokenType::MINUS: case TokenType::INCREMENT:
				case TokenType::DECREMENT:
				case VAL_BOOL:     case VAL_INT:    case VAL_INT8:
				case VAL_INT16:    case VAL_INT32:  case VAL_INT64:
				case VAL_UINT:     case VAL_UINT8:  case VAL_UINT16:
				case VAL_UINT32:   case VAL_UINT64: case VAL_FLOAT:
				case VAL_DOUBLE:   case VAL_CHAR:   case VAL_STRING:
				case THIS:         case IDENTIFIER: case NEW:
				case OPEN_BRACKET: case OPEN_PAREN: case IF:
				case SWITCH:       case TEMP:
					return true;
				default:
					return false;
			}
		}

		Node* ParseStatement() {
			auto flags = ParseFlags();

			Node* node = nullptr;

			switch (PeekNextConcreteToken()->type) {
				case TokenType::VAR: node = ParseVarDecl(); break;
				case DEF: node = ParseFunction(); break;
				case EXTERN: node = ParseExternFunction(); break;
				case NAMESPACE: node = ParseNamespace(); break;
				case ENUM: node = ParseEnum(); break;
				case CLASS: node = ParseClass(); break;
				case AGGREGATE: node = ParseAggregate(); break;
				case IMPORT: node = ParseImport(); break;
				case EXTEND: node = ParseExtend(); break;
				case GET: node = ParseGet(); break;
				case SET: node = ParseSet(); break;
				default: break;
			}

			// Parse remaining statements that don't support flags
			if (flags.size() == 0 && node == nullptr) {
				auto next = PeekNextConcreteToken();

				if (IsExpressionToken(next)) {
					node = ParseExpression();
				}

				switch (next->type) {
					case OPEN_CURLY:
						node = ParseLongBlock();
						break;
					case DELETE: {
						GetNextConcreteToken();
						auto expr = ParseExpression();
						if (expr == nullptr) { Expected("expression"); return nullptr; }
						node = CreateNode<DeleteStmt>(expr);
						break;
					}
					case BREAK:
						GetNextConcreteToken();
						node = CreateNode<BreakStmt>();
						break;
					case CONTINUE:
						GetNextConcreteToken();
						node = CreateNode<ContinueStmt>();
						break;
					case YIELD: {
						GetNextConcreteToken();
						auto expr = ParseExpression();
						if (expr == nullptr) { Expected("expression"); return nullptr; }
						node = CreateNode<YieldStmt>(expr);
						break;
					}
					case FOR: node = ParseForLoop(); break;
					case FOREACH: node = ParseForEachLoop(); break;
					case WHILE: node = ParseWhileLoop(); break;
					case DO: node = ParseDoWhileLoop(); break;
					case FOREVER: node = ParseForeverLoop(); break;
					case TRY: node = ParseTryCatch(); break;
					default: break;
				}
			}

			if (node != nullptr) {
				node->flags.insert(node->flags.end(), flags.begin(), flags.end());
			}

			return node;
		}

		GetterStmt* ParseGet() {
			if (!Expect(GET)) return nullptr;
			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }
			return CreateNode<GetterStmt>(body);
		}

		SetterStmt* ParseSet() {
			if (!Expect(SET)) return nullptr;
			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }
			return CreateNode<SetterStmt>(body);
		}

		ClassStmt* ParseClass() {
			if (!Expect(CLASS)) return nullptr;

			Identifier* name = nullptr;
			std::vector<Identifier*> supers;

			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;

			name = CreateNode<NamedIDExpr>(token->value);

			if (PeekNextConcreteToken()->type == COLON) {
				GetNextConcreteToken();

				auto base = ParseLongID();
				if (base == nullptr) { Expected("base class"); return nullptr; }
				supers.push_back(base);

				while (PeekNextConcreteToken()->type == COMMA) {
					GetNextConcreteToken();

					auto base = ParseLongID();
					if (base == nullptr) { Expected("base class"); return nullptr; }
					supers.push_back(base);
				}
			}

			auto body = ParseClassBody();

			return CreateNode<ClassStmt>(name, supers, body);
		}

		BlockExpr* ParseClassBody() {
			if (!Expect(OPEN_CURLY)) return nullptr;

			auto statements = std::vector<Node*>();
			auto next = PeekNextConcreteToken();

			while (next->type == SEMICOLON) {
				GetNextConcreteToken();
				next = PeekNextConcreteToken();
			}

			while (next->type != CLOSE_CURLY && next->type != TOKEN_EOF) {
				auto stmt = ParseClassStatement();

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

			if (!Expect(CLOSE_CURLY)) return nullptr;

			return CreateNode<LongBlockExpr>(statements);
		}

		Node* ParseClassStatement() {
			auto flags = ParseFlags();

			Node* node = nullptr;

			switch (PeekNextConcreteToken()->type) {
				case TokenType::VAR: node = ParseVarDecl(); break;
				case DEF: node = ParseFunction(); break;
				case EXTERN: node = ParseExternFunction(); break;
				case AGGREGATE: node = ParseAggregate(); break;
				case IMPORT: node = ParseImport(); break;
				case EXTEND: node = ParseExtend(); break;
				case PROPERTY: node = ParseProperty(); break;
				case ENUM: node = ParseEnum(); break;
				case CLASS: node = ParseClass(); break;
				default: break;
			}

			if (node != nullptr) {
				node->flags.insert(node->flags.end(), flags.begin(), flags.end());
			}

			return node;
		}

		PropertyStmt* ParseProperty() {
			if (!Expect(PROPERTY)) return nullptr;

			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;

			auto name = CreateNode<NamedIDExpr>(token->value);
			Type* type = nullptr;

			if (PeekNextConcreteToken()->type == ARROW) {
				GetNextConcreteToken();

				type = ParseType();
				if (type == nullptr) { Expected("type"); return nullptr; }
			}

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			return CreateNode<PropertyStmt>(name, type, body);
		}

		ExtendStmt* ParseExtend() {
			if (!Expect(EXTEND)) return nullptr;

			Identifier* name = nullptr;
			std::vector<Identifier*> supers;

			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;

			name = CreateNode<NamedIDExpr>(token->value);

			if (PeekNextConcreteToken()->type == COLON) {
				GetNextConcreteToken();

				auto base = ParseLongID();
				if (base == nullptr) { Expected("base class"); return nullptr; }
				supers.push_back(base);

				while (PeekNextConcreteToken()->type == COMMA) {
					GetNextConcreteToken();

					auto base = ParseLongID();
					if (base == nullptr) { Expected("base class"); return nullptr; }
					supers.push_back(base);
				}
			}

			auto body = ParseClassBody();

			return CreateNode<ExtendStmt>(name, supers, body);
		}

		ImportStmt* ParseImport() {
			if (!Expect(IMPORT)) return nullptr;
			auto name = ParseLongID();
			if (name == nullptr) { Expected("identifier"); return nullptr; }
			return CreateNode<ImportStmt>(name);
		}

		AggregateStmt* ParseAggregate() {
			if (!Expect(AGGREGATE)) return nullptr;

			Identifier* name = nullptr;

			if (PeekNextConcreteToken()->type == IDENTIFIER) {
				name = ParseLongID();
				if (name == nullptr) { Expected("identifier"); return nullptr; }
			}

			auto block = ParseLongBlock();
			if (block == nullptr) { Expected("block"); return nullptr; }

			return CreateNode<AggregateStmt>(name, block);
		}

		TryExpr* ParseTryCatch() {
			if (!Expect(TRY)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			std::vector<CatchBlock*> catches;

			while (PeekNextConcreteToken()->type == CATCH) {
				GetNextConcreteToken();

				if (!Expect(OPEN_PAREN)) return nullptr;

				auto variable = ParseVarDecl();
				if (variable == nullptr) { Expected("variable"); return nullptr; }

				if (!Expect(CLOSE_PAREN)) return nullptr;

				auto block = ParseBlock();
				if (block == nullptr) { Expected("block"); return nullptr; }

				catches.push_back(CreateNode<CatchBlock>(variable, block));
			}

			BlockExpr* finallyBlock = nullptr;

			if (PeekNextConcreteToken()->type == FINALLY) {
				GetNextConcreteToken();

				finallyBlock = ParseBlock();
				if (finallyBlock == nullptr) { Expected("block"); return nullptr; }
			}

			return CreateNode<TryExpr>(body, catches, finallyBlock);
		}

		bool IsForComponentToken(Token* tok) {
			return tok->type == VAR || IsExpressionToken(tok);
		}

		Expression* ParseForComponent() {
			return PeekNextConcreteToken()->type == VAR ? ParseVarDecl() : ParseExpression();
		}

		LoopStmt* ParseForLoop() {
			if (!Expect(FOR)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			Expression* initializer = nullptr;
			Expression* condition = nullptr;
			Expression* afterthought = nullptr;

			if (IsForComponentToken(PeekNextConcreteToken())) initializer = ParseForComponent();

			if (!Expect(SEMICOLON)) return nullptr;

			if (IsForComponentToken(PeekNextConcreteToken())) condition = ParseForComponent();

			if (!Expect(SEMICOLON)) return nullptr;

			if (IsForComponentToken(PeekNextConcreteToken())) afterthought = ParseForComponent();

			if (!Expect(CLOSE_PAREN)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			return CreateNode<LoopStmt>(initializer, condition, afterthought, LoopConditionCheck::BEFORE, body);
		}

		ForeachStmt* ParseForEachLoop() {
			if (!Expect(FOREACH)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			auto LHS = ParseVarDecl();
			if (LHS == nullptr) { Expected("variable declaration"); return nullptr; }

			if (!Expect(IN)) return nullptr;

			auto RHS = ParseExpression();
			if (RHS == nullptr) { Expected("expression"); return nullptr; }

			if (!Expect(CLOSE_PAREN)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			return CreateNode<ForeachStmt>(LHS, RHS, body);
		}

		LoopStmt* ParseWhileLoop() {
			if (!Expect(WHILE)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			auto expr = ParseExpression();
			if (expr == nullptr) { Expected("expression"); return nullptr; }

			if (!Expect(CLOSE_PAREN)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			return CreateNode<LoopStmt>(nullptr, expr, nullptr, LoopConditionCheck::BEFORE, body);
		}

		LoopStmt* ParseDoWhileLoop() {
			if (!Expect(DO)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }

			if (!Expect(WHILE)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			auto expr = ParseExpression();
			if (expr == nullptr) { Expected("expression"); return nullptr; }

			if (!Expect(CLOSE_PAREN)) return nullptr;

			return CreateNode<LoopStmt>(nullptr, expr, nullptr, LoopConditionCheck::AFTER, body);
		}

		LoopStmt* ParseForeverLoop() {
			if (!Expect(FOREVER)) return nullptr;
			auto body = ParseBlock();
			if (body == nullptr) { Expected("block"); return nullptr; }
			return CreateNode<LoopStmt>(nullptr, nullptr, nullptr, LoopConditionCheck::BEFORE, body);
		}

		EnumStmt* ParseEnum() {
			if (!Expect(ENUM)) return nullptr;
			Identifier* name = nullptr;
			std::vector<EnumValue*> values;

			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;
			name = CreateNode<NamedIDExpr>(token->value);

			if (!Expect(OPEN_CURLY)) return nullptr;

			if (PeekNextConcreteToken()->type == IDENTIFIER) {
				values = ParseEnumValues();
			}

			if (!Expect(CLOSE_CURLY)) return nullptr;

			return CreateNode<EnumStmt>(name, values);
		}

		std::vector<EnumValue*> ParseEnumValues() {
			std::vector<EnumValue*> values;

			auto value = ParseEnumValue();
			if (value == nullptr) { Expected("identitfer"); return std::vector<EnumValue*>(); }
			values.push_back(value);

			while (PeekNextConcreteToken()->type == COMMA) {
				GetNextConcreteToken();

				if (PeekNextConcreteToken()->type != IDENTIFIER) {
					break;
				}

				value = ParseEnumValue();
				if (value == nullptr) { Expected("identitfer"); return std::vector<EnumValue*>(); }
				values.push_back(value);
			}

			return values;
		}

		EnumValue* ParseEnumValue() {
			Identifier* name = nullptr;
			std::vector<VarDeclExpr*> params;

			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;
			name = CreateNode<NamedIDExpr>(token->value);

			if (PeekNextConcreteToken()->type == OPEN_PAREN) {
				GetNextConcreteToken();

				params = ParseParameterList();

				if (!Expect(CLOSE_PAREN)) return nullptr;
			}


			return CreateNode<EnumValue>(name, params);
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

		ExternFuncStmt* ParseExternFunction() {
			if (!Expect(EXTERN)) return nullptr;
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
			if (!Expect(ARROW)) return nullptr;

			retType = ParseType();
			if (retType == nullptr) {
				Expected("type");
				return nullptr;
			}

			return CreateNode<ExternFuncStmt>(id, params, retType);
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

			return CreateNode<FunctionExpr>(id, nullptr, params, retType, body);
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
			auto LHS = ParseUnary();
			if (LHS == nullptr) { Expected("expression"); return nullptr; }

			if (IsBinOpToken(mStream.peek())) {
				LHS = ParseBinOpExpression(LHS, 0);
			}

			if (mStream.peek()->type == AS) {
				mStream.get();

				auto type = ParseType();
				if (type == nullptr) { Expected("type"); return nullptr; }

				LHS = CreateNode<CastExpr>(type, LHS);
			}

			return LHS;
		}

		Expression* ParseBinOpExpression(Expression* LHS, int minPrecedence) {
			auto next = mStream.peek();

			while (GetOperatorPrecedence(next->type) >= minPrecedence) {
				auto op = next->type;
				mStream.get();

				auto RHS = ParseUnary();
				if (RHS == nullptr) { Expected("expression"); return nullptr; }

				next = mStream.peek();

				while ((GetAssociativity(next->type) == LEFT &&
				        GetOperatorPrecedence(next->type) > GetOperatorPrecedence(op)) ||
				       (GetAssociativity(next->type) == RIGHT &&
				        GetOperatorPrecedence(next->type) == GetOperatorPrecedence(op))) {
					RHS = ParseBinOpExpression(RHS, GetOperatorPrecedence(next->type));
					next = mStream.peek();
				}

				LHS = CreateNode<BinOpExpr>(LHS, GetBinOp(op), RHS);
			}

			if (mStream.peek()->type == QUESTION) {
				mStream.get();

				auto trueValue = ParseExpression();
				if (trueValue == nullptr) { Expected("expression"); return nullptr; }

				if (!Expect(COLON)) return nullptr;

				auto falseValue = ParseExpression();
				if (falseValue == nullptr) { Expected("expression"); return nullptr; }

				return CreateNode<TernaryExpr>(LHS, trueValue, falseValue);
			}

			return LHS;
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
					if (inner == nullptr) { Expected("expression"); return nullptr; }
					return CreateNode<UnaryExpr>(GetUnaryOp(token->type), UnaryOrder::PREFIX, inner);
				case TokenType::NEW:
					GetNextConcreteToken();
					inner = ParseExpression();
					if (inner == nullptr) { Expected("expression"); return nullptr; }
					return CreateNode<NewExpr>(inner);
				default: break;
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
				default: break;
			}

			return ParseOperation();
		}


		bool IsOperationToken(Token* tok) {
			switch (tok->type) {
				case TokenType::INCREMENT: case TokenType::DECREMENT:
				case OPEN_PAREN: case OPEN_BRACKET: case DOT:
					return true;
				default:
					return false;
			}
		}

		/// Operation _or_ primary
		/// The operations are: function call, array access, member access, and postfix unary operations
		Expression* ParseOperation() {
			Expression* primary = ParsePrimary();

			while (IsOperationToken(mStream.peek())) {
				switch (mStream.peek()->type) {
					case TokenType::INCREMENT: case TokenType::DECREMENT:
						primary = CreateNode<UnaryExpr>(GetUnaryOp(mStream.get()->type), UnaryOrder::POSTFIX, primary);
						break;
					case TokenType::OPEN_PAREN: // function call
						if (!Expect(OPEN_PAREN)) return nullptr;
						primary = CreateNode<FunctionCallExpr>(primary, ParseOptArgList());
						if (!Expect(CLOSE_PAREN)) return nullptr;
						break;
					case TokenType::OPEN_BRACKET: {
						if (!Expect(OPEN_BRACKET)) return nullptr;
						auto RHS = ParseExpression();
						if (RHS == nullptr) { Expected("expression"); return nullptr; }
						primary = CreateNode<ArrayAccessExpr>(primary, RHS);
						if (!Expect(CLOSE_BRACKET)) return nullptr;
						break;
					}
					case TokenType::DOT: {
						mStream.get();
						auto RHS = ParseIdentifier();
						if (RHS == nullptr) { Expected("identifier"); return nullptr; }
						primary = CreateNode<MemberAccessExpr>(primary, RHS);
						break;
					}
					default: break;
				}
			}

			return primary;
		}

		std::vector<Expression*> ParseOptArgList() {
			std::vector<Expression*> args;

			if (IsExpressionToken(PeekNextConcreteToken())) args = ParseArgList();

			return args;
		}

		std::vector<Expression*> ParseArgList() {
			std::vector<Expression*> args;

			auto arg = ParseArgument();
			if (arg == nullptr) { Expected("expression"); return std::vector<Expression*>(); }
			args.push_back(arg);

			while (PeekNextConcreteToken()->type == COMMA) {
				GetNextConcreteToken();

				arg = ParseArgument();
				if (arg == nullptr) { Expected("expression"); return std::vector<Expression*>(); }
				args.push_back(arg);
			}

			return args;
		}

		Expression* ParseArgument() {
			auto lookahead = mStream.peek(2);
			if (lookahead[0]->type == IDENTIFIER && lookahead[1]->type == COLON) {
				auto id = CreateNode<ReferenceIDExpr>(mStream.get()->value);

				if (!Expect(COLON)) return nullptr;

				auto val = ParseExpression();
				if (val == nullptr) { Expected("Expression"); }

				return CreateNode<NamedExpr>(id, val);
			} else return ParseExpression();
		}

		Identifier* ParseIdentifier() {
			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;
			return CreateNode<ReferenceIDExpr>(token->value);
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
				case OPEN_BRACKET: return ParseArray();
				case OPEN_PAREN: return ParseParenExpr();
				case IDENTIFIER: return CreateNode<ReferenceIDExpr>(GetNextConcreteToken()->value);
				case THIS: GetNextConcreteToken(); return CreateNode<ThisID>();
				case IF: return ParseIf();
				case SWITCH: return ParseSwitch();
				case TEMP: GetNextConcreteToken(); return CreateNode<TempIDExpr>();
				default:
					Expected("value", token);
					return nullptr;
			}
		}

		bool IsSwitchPatternToken(Token* tok) {
			switch (tok->type) {
				case VAL_BOOL:     case VAL_INT:      case VAL_INT8:
				case VAL_INT16:    case VAL_INT32:    case VAL_INT64:
				case VAL_UINT:     case VAL_UINT8:    case VAL_UINT16:
				case VAL_UINT32:   case VAL_UINT64:   case VAL_FLOAT:
				case VAL_DOUBLE:   case VAL_CHAR:     case VAL_STRING:
				case IDENTIFIER:   case OPEN_BRACKET: case OPEN_PAREN:
				case TEMP:
					return true;
				default:
					return false;
			}
		}

		SwitchPattern* ParseSwitchPattern() {
			std::vector<Expression*> matches;

			auto match = ParseSwitchPatternMatch();
			if (match == nullptr) { Expected("pattern"); return nullptr; }
			matches.push_back(match);

			while (PeekNextConcreteToken()->type == COMMA) {
				GetNextConcreteToken();

				auto match = ParseSwitchPatternMatch();
				if (match == nullptr) { Expected("pattern"); return nullptr; }
				matches.push_back(match);
			}

			if (!Expect(COLON)) return nullptr;

			BlockExpr* value = nullptr;

			if (PeekNextConcreteToken()->type == OPEN_CURLY) {
				GetNextConcreteToken();

				value = CreateNode<LongBlockExpr>(ParseStatements());

				if (!Expect(CLOSE_CURLY)) return nullptr;
			} else {
				Expression* expr = ParseExpression();

				if (expr != nullptr && mStream.peek()->type == SEMICOLON) {
					mStream.get();
					value = CreateNode<LongBlockExpr>(std::vector<Node*>({
						CreateNode<ExprStmt>(expr)
					}));
				} else {
					value = CreateNode<LongBlockExpr>(std::vector<Node*>({ expr }));
				}
			}

			if (value == nullptr) { Expected("expression"); return nullptr; }
			return CreateNode<SwitchPattern>(matches, value);
		}

		Expression* ParseEnumMatch() {
			auto token = GetNextConcreteToken();
			if (!Expect(IDENTIFIER, token)) return nullptr;

			Identifier* id = CreateNode<ReferenceIDExpr>(token->value);

			while (mStream.peek()->type == DOT) {
				mStream.get();

				token = GetNextConcreteToken();
				if (!Expect(IDENTIFIER, token)) return nullptr;

				id = CreateNode<AccessIDExpr>(id, CreateNode<ReferenceIDExpr>(token->value));
			}

			if (mStream.peek()->type == OPEN_PAREN) {
				mStream.get();

				std::vector<Expression*> args;

				if (IsSwitchPatternToken(PeekNextConcreteToken())) {
					auto arg = ParseSwitchPatternMatch();
					if (arg == nullptr) { Expected("expression"); return nullptr; }
					args.push_back(arg);

					while (PeekNextConcreteToken()->type == COMMA) {
						GetNextConcreteToken();

						auto arg = ParseSwitchPatternMatch();
						if (arg == nullptr) { Expected("expression"); return nullptr; }
						args.push_back(arg);
					}
				}

				if (!Expect(CLOSE_PAREN)) return nullptr;

				return CreateNode<FunctionCallExpr>(id, args);
			} else {
				return id;
			}
		}

		Expression* ParseSwitchPatternMatch() {
			switch (PeekNextConcreteToken()->type) {
				case IDENTIFIER: return ParseEnumMatch();
				default: return ParsePrimary();
			}
		}

		SwitchExpr* ParseSwitch() {
			if (!Expect(SWITCH)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			auto expr = ParseExpression();
			if (expr == nullptr) { Expected("Expression"); return nullptr; }

			if (!Expect(CLOSE_PAREN)) return nullptr;

			if (!Expect(OPEN_CURLY)) return nullptr;

			std::vector<SwitchPattern*> patterns;

			if (IsSwitchPatternToken(PeekNextConcreteToken())) {
				auto pattern = ParseSwitchPattern();
				if (pattern == nullptr) { Expected("pattern"); return nullptr; }
				patterns.push_back(pattern);

				while (PeekNextConcreteToken()->type == COMMA) {
					GetNextConcreteToken();

					if (!IsSwitchPatternToken(PeekNextConcreteToken())) break;

					auto pattern = ParseSwitchPattern();
					if (pattern == nullptr) { Expected("pattern"); return nullptr; }
					patterns.push_back(pattern);
				}
			}

			if (!Expect(CLOSE_CURLY)) return nullptr;

			return CreateNode<SwitchExpr>(expr, patterns);
		}

		IfExpr* ParseIf() {
			if (!Expect(IF)) return nullptr;
			if (!Expect(OPEN_PAREN)) return nullptr;

			auto condition = ParseExpression();
			if (condition == nullptr) { Expected("condition"); return nullptr; }

			if (!Expect(CLOSE_PAREN)) return nullptr;

			auto body = ParseBlock();
			if (body == nullptr) { Expected("body"); return nullptr; }

			std::vector<ConditionalBlock*> elses;
			elses.push_back(CreateNode<ConditionalBlock>(condition, body));

			auto next = PeekNextConcreteToken();
			while (next->type == ELIF || next->type == ELSE) {
				GetNextConcreteToken();

				if (next->type == ELIF) {
					if (!Expect(OPEN_PAREN)) return nullptr;

					auto condition = ParseExpression();
					if (condition == nullptr) { Expected("condition"); return nullptr; }

					if (!Expect(CLOSE_PAREN)) return nullptr;

					auto body = ParseBlock();
					if (body == nullptr) { Expected("body"); return nullptr; }

					elses.push_back(CreateNode<ConditionalBlock>(condition, body));
				} else if (next->type == ELSE) {
					auto body = ParseBlock();
					if (body == nullptr) { Expected("body"); return nullptr; }

					elses.push_back(CreateNode<ConditionalBlock>(nullptr, body));
				}

				next = PeekNextConcreteToken();
			}

			return CreateNode<IfExpr>(elses);
		}

		/// Parses an expression surrounded by parens or a tuple
		Expression* ParseParenExpr() {
			if (!Expect(OPEN_PAREN)) return nullptr;

			std::vector<Expression*> exprs;

			auto expr = ParseArgument();
			if (expr == nullptr) { Expected("expression"); return nullptr; }
			exprs.push_back(expr);

			int numCommas = 0;

			while (PeekNextConcreteToken()->type == COMMA) {
				GetNextConcreteToken();
				numCommas++;

				if (IsExpressionToken(PeekNextConcreteToken())) {
					expr = ParseArgument();
					if (expr == nullptr) { Expected("expression"); return nullptr; }
					exprs.push_back(expr);
				}
			}

			if (!Expect(CLOSE_PAREN)) return nullptr;

			if (numCommas == 0 && !isA<NamedExpr>(exprs.front())) {
				return exprs.front();
			} else {
				return CreateNode<TupleExpr>(exprs);
			}
		}

		Expression* ParseArray() {
			if (!Expect(OPEN_BRACKET)) return nullptr;

			Expression* array = nullptr;

			if (IsExpressionToken(PeekNextConcreteToken())) {
				auto first = ParseExpression();
				if (first == nullptr) { Expected("expression"); return nullptr; }

				if (PeekNextConcreteToken()->type == COMMA) {
					std::vector<Expression*> values({ first });

					while (PeekNextConcreteToken()->type == COMMA) {
						GetNextConcreteToken();

						auto value = ParseExpression();
						if (value == nullptr) { Expected("expression"); return nullptr; }
						values.push_back(value);
					}

					array = CreateNode<ArrayExpr>(values);
				} else if (PeekNextConcreteToken()->type == INCLUSIVE_RANGE) {
					GetNextConcreteToken();
					auto second = ParseExpression();
					if (second == nullptr) { Expected("expression"); return nullptr; }

					array = CreateNode<ArrayRangeExpr>(first, ArrayRangeType::INCLUSIVE, second);
				} else if (PeekNextConcreteToken()->type == EXCLUSIVE_RANGE) {
					GetNextConcreteToken();
					auto second = ParseExpression();
					if (second == nullptr) { Expected("expression"); return nullptr; }

					array = CreateNode<ArrayRangeExpr>(first, ArrayRangeType::EXCLUSIVE, second);
				} else { // array with single element
					array = CreateNode<ArrayExpr>(std::vector<Expression*>({ first }));
				}
			} else { // empty array
				array = CreateNode<ArrayExpr>(std::vector<Expression*>());
			}

			if (!Expect(CLOSE_BRACKET)) return nullptr;

			return array;
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
