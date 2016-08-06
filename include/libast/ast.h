/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <type_traits>

#include "type.h"

namespace orange { namespace ast {
	struct Flag;
	struct Identifier;
	struct Expression;
	struct BlockExpr;
	struct VarDeclExpr;

	struct Node {
	protected:
		Node() { }

	public:
		int id;
		std::vector<Flag*> flags;

		virtual ~Node() { }
	};

	struct Statement : Node {
	protected:
		Statement() { }
	};

	struct CommentStmt : Statement {
	public:
		std::string value;

		CommentStmt() { }
		CommentStmt(std::string value) : value(value) { }
	};

	enum LoopConditionCheck { BEFORE, AFTER };

	struct LoopStmt : Statement {
	public:
		Expression* initializer = nullptr;
		Expression* condition = nullptr;
		Expression* afterthought = nullptr;

		LoopConditionCheck check;

		BlockExpr* body = nullptr;

		LoopStmt() { }
		LoopStmt(Expression* initializer, Expression* condition, Expression* afterthought,
		         LoopConditionCheck check, BlockExpr* body) :
			initializer(initializer), condition(condition), afterthought(afterthought), check(check), body(body) { }
	};

	struct BreakStmt : Statement { };

	struct ContinueStmt : Statement { };

	struct ReturnStmt : Statement {
	public:
		Expression* value = nullptr;

		ReturnStmt() { }
		ReturnStmt(Expression* value) : value(value) { }
	};

	struct ExternFuncStmt : Statement {
	public:
		std::string name = "";
		std::vector<VarDeclExpr*> params;
		Type* retType = nullptr;

		ExternFuncStmt() { }
		ExternFuncStmt(std::string name, std::vector<VarDeclExpr*> params, Type* retType) :
			name(name), params(params), retType(retType) { }
	};

	struct EnumStmt : Statement {
	public:
		std::string name = nullptr;
		std::vector<std::string> values;

		EnumStmt() { }
		EnumStmt(std::string name, std::vector<std::string> values) :
			name(name), values(values) { }
	};

	struct ClassStmt : Statement {
	public:
		Identifier* name = nullptr;
		std::vector<Identifier*> supers;
		BlockExpr* body = nullptr;

		ClassStmt() { }
		ClassStmt(Identifier* name, std::vector<Identifier*> supers, BlockExpr* body) :
			name(name), supers(supers), body(body) { }
	};

	struct InterfaceStmt : Statement {
	public:
		Identifier* name = nullptr;
		BlockExpr* body = nullptr;

		InterfaceStmt() { }
		InterfaceStmt(Identifier* name, BlockExpr* body) :
			name(name), body(body) { }
	};

	struct NamespaceStmt : Statement {
	public:
		Identifier* name = nullptr;
		BlockExpr* body = nullptr;

		NamespaceStmt() { }
		NamespaceStmt(Identifier* name, BlockExpr* body) :
			name(name), body(body) { }
	};

	struct ImportStmt : Statement {
	public:
		Identifier* name = nullptr;

		ImportStmt() { }
		ImportStmt(Identifier* name) : name(name) { }
	};

	struct ThrowStmt : Statement {
	public:
		Expression* exception = nullptr;

		ThrowStmt() { }
		ThrowStmt(Expression* exception) : exception(exception) { }
	};

	struct DeleteStmt : Statement {
	public:
		Expression* deallocation = nullptr;

		DeleteStmt() { }
		DeleteStmt(Expression* dealloc) : deallocation(dealloc) { }
	};

	struct ExprStmt : Statement {
	public:
		Expression* expression = nullptr;

		ExprStmt() { }
		ExprStmt(Expression* expression) : expression(expression) { }
	};

	//
	// Expressions
	//

	struct Expression : Node {
	protected:
		Expression() { }
	};

	struct VarDeclExpr : Expression {
	public:
		std::string name;
		Type* type;
		Expression* value = nullptr;

		VarDeclExpr() { }
		VarDeclExpr(std::string name, Type* type, Expression* value) : name(name), type(type), value(value) { }
	};

	struct Value : Expression { };

	struct BoolValue : Value {
	public:
		bool value;

		BoolValue() { }
		BoolValue(bool value) : value(value) { }
	};

	struct IntValue : Value {
	public:
		int64_t value;
		Type* type = new BuiltinType(BuiltinTypeKind::INT);

		IntValue() { }
		IntValue(int64_t value) : value(value) { }
		IntValue(int64_t value, Type* ty) : value(value), type(ty) { }
	};

	struct UIntValue : Value {
	public:
		uint64_t value;
		Type* type = new BuiltinType(BuiltinTypeKind::UINT);

		UIntValue() { }
		UIntValue(uint64_t value) : value(value) { }
		UIntValue(uint64_t value, Type* ty) : value(value), type(ty) { }
	};

	struct FloatValue : Value {
	public:
		float value;

		FloatValue() { }
		FloatValue(float value) : value(value) { }
	};

	struct DoubleValue : Value {
	public:
		double value;

		DoubleValue() { }
		DoubleValue(double value) : value(value) { }
	};

	struct StringValue : Value {
	public:
		std::string value;

		StringValue() { }
		StringValue(std::string value) : value(value) { }
	};

	struct CharValue : Value {
	public:
		int64_t value;

		CharValue() { }
		CharValue(int64_t value) : value(value) { }
	};

	struct Identifier : Expression {
	protected:
		Identifier() { }
	};

	struct ThisID : Identifier {
	public:
		ThisID() { }
	};

	// A reference to a named node.
	struct ReferenceIDExpr : Identifier {
	public:
		std::string name;

		ReferenceIDExpr() { }
		ReferenceIDExpr(std::string name) : name(name) { }
	};

	// A named node, mostly in the context of it being declared.
	struct NamedIDExpr : Identifier {
	public:
		std::string name;

		NamedIDExpr() { }
		NamedIDExpr(std::string name) : name(name) { }
	};

	struct DtorIDExpr : Identifier {
	public:
		NamedIDExpr* base = nullptr;

		DtorIDExpr() { }
		DtorIDExpr(NamedIDExpr* base) : base(base) { }
	};

	struct AccessIDExpr : Identifier {
	public:
		Identifier* LHS = nullptr;
		Identifier* RHS = nullptr;

		AccessIDExpr() { }
		AccessIDExpr(Identifier* LHS, Identifier* RHS) : LHS(LHS), RHS(RHS) { }
	};

	struct BlockExpr : Expression { };

	struct LongBlockExpr : BlockExpr {
	public:
		std::vector<Node*> statements;

		LongBlockExpr() { }
		LongBlockExpr(std::vector<Node*> statements) : statements(statements) { }
	};

	struct ShortBlockExpr : BlockExpr {
	public:
		Node* statement = nullptr;

		ShortBlockExpr() { }
		ShortBlockExpr(Node* statement) : statement(statement) { }
	};

	enum BinOp {
		ADD, SUBTRACT, DIVIDE, MULTIPLY,
		REMAINDER, BIT_OR, BIT_AND, BIT_XOR,
		SHIFT_LEFT, SHIFT_RIGHT, ASSIGN, EQUALS,
		PLUS_ASSIGN, MINUS_ASSIGN, TIMES_ASSIGN, DIVIDE_ASSIGN,
		REMAINDER_ASSIGN, SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, BIT_OR_ASSIGN,
		BIT_AND_ASSIGN, BIT_XOR_ASSIGN, LESS_THAN, GREATER_THAN,
		LEQ, GEQ, NEQ, AND, OR
	};

	struct BinOpExpr : Expression {
	public:
		Expression* LHS = nullptr;
		BinOp op;
		Expression* RHS = nullptr;

		BinOpExpr() { }
		BinOpExpr(Expression* LHS, BinOp op, Expression* RHS) :
			LHS(LHS), op(op), RHS(RHS) { }
	};

	enum UnaryOp { INCREMENT, DECREMENT, MINUS, NOT, TILDE, TIMES, REFERENCE };
	enum UnaryOrder { PREFIX, POSTFIX };

	struct UnaryExpr : Expression {
	public:
		UnaryOp op;
		UnaryOrder order;
		Expression* LHS = nullptr;

		UnaryExpr() { }
		UnaryExpr(UnaryOp op, UnaryOrder order, Expression* LHS) : op(op), order(order), LHS(LHS) { }
	};

	struct ArrayExpr : Expression {
	public:
		std::vector<Expression*> values;

		ArrayExpr() { }
		ArrayExpr(std::vector<Expression*> values) : values(values) { }
	};

	struct ArrayAccessExpr : Expression {
	public:
		Expression* expression = nullptr;
		Expression* index = nullptr;

		ArrayAccessExpr () { }
		ArrayAccessExpr (Expression* expression, Expression* index) :
			expression(expression), index(index) { }
	};

	struct MemberAccessExpr : Expression {
	public:
		Expression* LHS = nullptr;
		Identifier* RHS = nullptr;

		MemberAccessExpr () { }
		MemberAccessExpr (Expression* LHS, Identifier* RHS) :
			LHS(LHS), RHS(RHS) { }
	};

	struct ConditionalBlock : Expression {
	public:
		Expression* condition = nullptr;
		BlockExpr* block = nullptr;

		ConditionalBlock() { }
		ConditionalBlock(Expression* condition, BlockExpr* block) : condition(condition), block(block) { }
	};

	struct IfExpr : Expression {
	public:
		std::vector<ConditionalBlock*> blocks;

		IfExpr() { }
		IfExpr(std::vector<ConditionalBlock*> blocks) : blocks(blocks) { }
	};

	struct TernaryExpr : Expression {
	public:
		Expression* condition = nullptr;
		Expression* trueValue = nullptr;
		Expression* falseValue = nullptr;

		TernaryExpr() { }
		TernaryExpr(Expression* condition, Expression* trueValue, Expression* falseValue) :
			condition(condition), trueValue(trueValue), falseValue(falseValue) { }
	};

	struct FunctionExpr : Expression {
	public:
		std::string name;
		std::vector<VarDeclExpr*> params;
		Type* retType = nullptr;
		BlockExpr* block = nullptr;

		FunctionExpr() { }
		FunctionExpr(std::string name, std::vector<VarDeclExpr*> params, Type* retType, BlockExpr* block) :
			name(name), params(params), retType(retType), block(block) { }
	};

	struct CatchBlock : Expression {
	public:
		VarDeclExpr* exception = nullptr;
		BlockExpr* block = nullptr;

		CatchBlock() { }
		CatchBlock(VarDeclExpr* exception, BlockExpr* block) :
			exception(exception), block(block) { }
	};

	struct TryExpr : Expression {
	public:
		BlockExpr* block = nullptr;
		std::vector<CatchBlock*> catches;
		BlockExpr* finally = nullptr;

		TryExpr() { }
		TryExpr(BlockExpr* block, std::vector<CatchBlock*> catches, BlockExpr* finally) :
			block(block), catches(catches), finally(finally) { }
	};

	struct CastExpr : Expression {
	public:
		Type* targetType = nullptr;
		Expression* expr = nullptr;

		CastExpr() { }
		CastExpr(Type* targetType, Expression* expr) :
			targetType(targetType), expr(expr) { }
	};

	struct FunctionCallExpr : Expression {
	public:
		Expression* function = nullptr;
		std::vector<Expression*> args;

		FunctionCallExpr() { }
		FunctionCallExpr(Expression* function, std::vector<Expression*> args) :
			function(function), args(args) { }
	};

	struct NewExpr : Expression {
	public:
		Expression* allocation = nullptr;

		NewExpr() { }
		NewExpr(Expression* allocation) : allocation(allocation) { }
	};

	/// Gets the next free ID for a node.
	int getNextID();

	template <class T, class... U>
	T* CreateNode(U&& ... params) {
		static_assert(std::is_base_of<Node, T>::value, "T must be a subclass of Node.");

		T* node = new T(std::forward<U>(params)...);
		node->id = getNextID();
		return node;
	}
}}
