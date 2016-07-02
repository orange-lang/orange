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

namespace orange { namespace ast {
	class Flag;
	class Type;
	class Identifier;
	class Expression;
	class BlockExpr;
	class VarDeclExpr;
	class EnumValue;

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
		Expression* initializer;
		Expression* condition;
		Expression* afterthought;

		LoopConditionCheck check;

		LoopStmt() { }
		LoopStmt(Expression* initializer, Expression* condition, Expression* afterthought, LoopConditionCheck check) :
			initializer(initializer), condition(condition), afterthought(afterthought), check(check) { }
	};

	struct ForeachStmt : Statement {
	public:
		VarDeclExpr* declaration;
		Expression* value;

		ForeachStmt() { }
		ForeachStmt(VarDeclExpr* declaration, Expression* value) :
			declaration(declaration), value(value) { }
	};

	struct BreakStmt : Statement { };

	struct ContinueStmt : Statement { };

	struct YieldStmt : Statement {
	public:
		Expression* value;

		YieldStmt() { }
		YieldStmt(Expression* value) : value(value) { }
	};

	struct ReturnStmt : Statement {
	public:
		Expression* value;

		ReturnStmt() { }
		ReturnStmt(Expression* value) : value(value) { }
	};

	struct AggregateStmt : Statement {
	public:
		Identifier* name;
		BlockExpr* body;

		AggregateStmt() { }
		AggregateStmt(Identifier* name, BlockExpr* body) :
			name(name), body(body) { }
	};

	struct ExternFuncStmt : Statement {
	public:
		Identifier* name;
		std::vector<VarDeclExpr*> params;
		Type* retType;

		ExternFuncStmt() { }
		ExternFuncStmt(Identifier* name, std::vector<VarDeclExpr*> params, Type* retType) :
			name(name), params(params), retType(retType) { }
	};

	struct EnumStmt : Statement {
	public:
		Identifier* name;
		std::vector<EnumValue*> values;

		EnumStmt() { }
		EnumStmt(Identifier* name, std::vector<EnumValue*> values) :
			name(name), values(values) { }
	};

	struct ClassStmt : Statement {
	public:
		Identifier* name;
		std::vector<Identifier*> supers;
		BlockExpr* body;

		ClassStmt() { }
		ClassStmt(Identifier* name, std::vector<Identifier*> supers, BlockExpr* body) :
			name(name), supers(supers), body(body) { }
	};

	struct InterfaceStmt : Statement {
	public:
		Identifier* name;
		BlockExpr* body;

		InterfaceStmt() { }
		InterfaceStmt(Identifier* name, BlockExpr* body) :
			name(name), body(body) { }
	};

	struct ExtendStmt : Statement {
	public:
		Identifier* name;
		std::vector<Identifier*> supers;
		BlockExpr* body;

		ExtendStmt() { }
		ExtendStmt(Identifier* name, std::vector<Identifier*> supers, BlockExpr* body) :
			name(name), supers(supers), body(body) { }
	};

	struct NamespaceStmt : Statement {
	public:
		Identifier* name;
		BlockExpr* body;

		NamespaceStmt() { }
		NamespaceStmt(Identifier* name, BlockExpr* body) :
			name(name), body(body) { }
	};

	struct ImportStmt : Statement {
	public:
		Identifier* name;

		ImportStmt() { }
		ImportStmt(Identifier* name) : name(name) { }
	};

	struct GetterStmt : Statement {
		BlockExpr* body;

		GetterStmt() { }
		GetterStmt(BlockExpr* body) : body(body) { }
	};

	struct SetterStmt : Statement {
		BlockExpr* body;

		SetterStmt() { }
		SetterStmt(BlockExpr* body) : body(body) { }
	};

	struct PropertyStmt : Statement {
		BlockExpr* body;

		PropertyStmt() { }
		PropertyStmt(BlockExpr* body) : body(body) { }
	};

	struct ThrowStmt : Statement {
	public:
		Expression* exception;

		ThrowStmt() { }
		ThrowStmt(Expression* exception) : exception(exception) { }
	};

	struct DeleteStmt : Statement {
	public:
		Expression* deallocation;

		DeleteStmt() { }
		DeleteStmt(Expression* dealloc) : deallocation(dealloc) { }
	};

	struct ExprStmt : Statement {
	public:
		Expression* expression;

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

	struct EnumValue : Expression {
	public:
		Identifier* name;
		std::vector<VarDeclExpr*> params;

		EnumValue() { }
		EnumValue(Identifier* name, std::vector<VarDeclExpr*> params) :
			name(name), params(params) { }
	};

	struct VarDeclExpr : Expression {
	public:
		std::vector<Identifier*> bindings;
		Type* type;
		Expression* value;

		VarDeclExpr() { }
		VarDeclExpr(std::vector<Identifier*> bindings, Type* type, Expression* value) :
			bindings(bindings), type(type), value(value) { }
	};

	struct Value : Expression { };

	struct IntValue : Value {
	public:
		int64_t value;

		IntValue() { }
		IntValue(int64_t value) : value(value) { }
	};

	struct UIntValue : Value {
	public:
		uint64_t value;

		UIntValue() { }
		UIntValue(uint64_t value) : value(value) { }
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

	struct NamedIDExpr : Identifier {
	public:
		std::string name;

		NamedIDExpr() { }
		NamedIDExpr(std::string name) : name(name) { }
	};

	struct TempIDExpr : Identifier {
	public:
		TempIDExpr() { }
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
		Node* statement;

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
		Expression* LHS;
		BinOp op;
		Expression* RHS;

		BinOpExpr() { }
		BinOpExpr(Expression* LHS, BinOp op, Expression* RHS) :
			LHS(LHS), op(op), RHS(RHS) { }
	};

	enum UnaryOp { INCREMENT, DECREMENT, MINUS, NOT, TILDE, TIMES, REFERENCE };

	struct UnaryExpr : Expression {
	public:
		UnaryOp op;
		Expression* LHS;

		UnaryExpr() { }
		UnaryExpr(UnaryOp op, Expression* LHS) : op(op), LHS(LHS) { }
	};

	struct TupleExpr : Expression {
	public:
		std::vector<Expression*> values;

		TupleExpr() { }
		TupleExpr(std::vector<Expression*> values) : values(values) { }
	};

	struct ArrayExpr : Expression {
	public:
		std::vector<Expression*> values;

		ArrayExpr() { }
		ArrayExpr(std::vector<Expression*> values) : values(values) { }
	};

	enum ArrayRangeType { EXCLUSIVE, INCLUSIVE };

	struct ArrayRangeExpr : Expression {
	public:
		Expression* LHS;
		ArrayRangeType type;
		Expression* RHS;

		ArrayRangeExpr() { }
		ArrayRangeExpr(Expression* LHS, ArrayRangeType type, Expression* RHS) :
			LHS(LHS), type(type), RHS(RHS) { }
	};

	struct ArrayAccessExpr : Expression {
	public:
		Expression* expression;
		Expression* index;

		ArrayAccessExpr () { }
		ArrayAccessExpr (Expression* expression, Expression* index) :
			expression(expression), index(index) { }
	};

	struct MemberAccessExpr : Expression {
	public:
		Expression* LHS;
		Identifier* RHS;

		MemberAccessExpr () { }
		MemberAccessExpr (Expression* LHS, Identifier* RHS) :
			LHS(LHS), RHS(RHS) { }
	};

	struct NamedExpr : Expression {
	public:
		Identifier* name;
		Expression* value;

		NamedExpr() { }
		NamedExpr(Identifier* name, Expression* value) :
			name(name), value(value) { }
	};

	struct ConditionalBlock : Expression {
	public:
		Expression* condition;
		BlockExpr* block;

		ConditionalBlock() { }
		ConditionalBlock(Expression* condition) : condition(condition) { }
	};

	struct IfExpr : Expression {
	public:
		std::vector<ConditionalBlock*> blocks;

		IfExpr() { }
		IfExpr(std::vector<ConditionalBlock*> blocks) : blocks(blocks) { }
	};

	struct TernaryExpr : Expression {
	public:
		Expression* condition;
		Expression* trueValue;
		Expression* falseValue;

		TernaryExpr() { }
		TernaryExpr(Expression* condition, Expression* trueValue, Expression* falseValue) :
			condition(condition), trueValue(trueValue), falseValue(falseValue) { }
	};

	struct SwitchPattern : Statement {
	public:
		std::vector<Expression*> patterns;
		BlockExpr* block;

		SwitchPattern() { }
		SwitchPattern(std::vector<Expression*> patterns, BlockExpr* block) :
			patterns(patterns), block(block) { }
	};

	struct SwitchExpr : Expression {
	public:
		Expression* condition;
		std::vector<SwitchPattern*> patterns;

		SwitchExpr() { }
		SwitchExpr(Expression* condition, std::vector<SwitchPattern*> patterns) :
			condition(condition), patterns(patterns) { }
	};

	struct Constraint : Node {
	protected:
		Constraint() { }
	};

	struct ClassConstraint : Constraint {
	public:
		Identifier* identifier;

		ClassConstraint() { }
		ClassConstraint(Identifier* identifier) : identifier(identifier) { }
	};

	struct DefaultCtorConstraint : Constraint {
	public:
		Identifier* identifier;

		DefaultCtorConstraint() { }
		DefaultCtorConstraint(Identifier* identifier) : identifier(identifier) { }
	};

	struct BaseConstraint : Constraint {
	public:
		Identifier* identifier;
		Identifier* base;

		BaseConstraint() { }
		BaseConstraint(Identifier* identifier, Identifier* base) :
			identifier(identifier), base(base) { }
	};

	struct DataConstraint : Constraint {
	public:
		Identifier* identifier;
		Type* dataType;

		DataConstraint() { }
		DataConstraint(Identifier* identifier, Type* dataType) :
			identifier(identifier), dataType(dataType) { }
	};

	struct TypeConstraint : Constraint {
	public:
		Identifier* identifier;
		Type* type;

		TypeConstraint() { }
		TypeConstraint(Identifier* identifier, Type* type) :
			identifier(identifier), type(type) { }
	};

	struct Generics : Node {
	public:
		std::vector<Identifier*> genericTypes;
		std::vector<Constraint*> constraints;

		Generics() { }
		Generics(std::vector<Identifier*> genericTypes, std::vector<Constraint*> constraints) :
			genericTypes(genericTypes), constraints(constraints) { }
	};

	struct FunctionExpr : Expression {
	public:
		Identifier* name;
		Generics* generics;
		std::vector<VarDeclExpr*> params;
		Type* retType;

		FunctionExpr() { }
		FunctionExpr(Identifier* name, Generics* generics, std::vector<VarDeclExpr*> params, Type* retType) :
			name(name), generics(generics), params(params), retType(retType) { }
	};

	struct CatchBlock : Expression {
	public:
		VarDeclExpr* exception;
		BlockExpr* block;

		CatchBlock() { }
		CatchBlock(VarDeclExpr* exception, BlockExpr* block) :
			exception(exception), block(block) { }
	};

	struct TryExpr : Expression {
	public:
		BlockExpr* block;
		std::vector<CatchBlock*> catches;
		BlockExpr* finally;

		TryExpr() { }
		TryExpr(BlockExpr* block, std::vector<CatchBlock*> catches, BlockExpr* finally) :
			block(block), catches(catches), finally(finally) { }
	};

	struct CastExpr : Expression {
	public:
		Type* targetType;
		Expression* expr;

		CastExpr() { }
		CastExpr(Type* targetType, Expression* expr) :
			targetType(targetType), expr(expr) { }
	};

	struct FunctionCallExpr : Expression {
	public:
		Expression* function;
		std::vector<Expression*> args;

		FunctionCallExpr() { }
		FunctionCallExpr(Expression* function, std::vector<Expression*> args) :
			function(function), args(args) { }
	};

	struct NewExpr : Expression {
	public:
		Expression* allocation;

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
