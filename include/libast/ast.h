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
	enum Operator {
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		MOD,
		LSHIFT,
		RSHIFT,
		AND,
		OR,
		LT,
		GT,
		LTE,
		GTE,
		NE,
		EQ,
		INCREMENT,
		DECREMENT,
		DOT,
		REFERENCE
	};

	enum OpPosition { PREFIX, POSTFIX };

	enum ArrayRangeType { INCLUSIVE, EXCLUSIVE };

	enum LoopConditionCheck { BEFORE_BODY, AFTER_BODY };

	enum PrivacyLevel {
		PRIVATE,
		PROTECTED,
		PUBLIC
	};

	struct Flag { };

	struct PrivacyFlag : Flag {
		PrivacyLevel level;

		PrivacyFlag(PrivacyLevel l) : level(l) { }
	};

	struct Node {
	protected:
		Node() { }

	public:
		int id;
		std::vector<Flag*> flags;

		virtual ~Node() { }
	};

	// Forward declare some commonly-used types.
	struct BlockExpr;
	struct Expression;
	struct Type;
	struct NamedType;
	struct GetterStmt;
	struct SetterStmt;
	struct ParamStmt;
	struct TypeConstraint;

	//
	// Statements
	//

	struct Statement : Node {
	protected:
		Statement() { }
	};

	struct PackageStmt : Statement {
		std::string name;

		PackageStmt() { }

		PackageStmt(std::string name) : name(name) { }
	};

	struct UsingStmt : Statement {
		std::string name;
		std::string alias;

		UsingStmt() { }

		UsingStmt(std::string name, std::string alias) :
			name(name), alias(alias) { }
	};

	struct ClassStmt : Statement {
		std::string name;
		std::vector<NamedType*> implements;
		BlockExpr* body;

		ClassStmt() { }

		ClassStmt(std::string name, std::vector<NamedType*> implements, BlockExpr* body) :
			name(name), implements(implements), body(body) { }
	};

	struct EnumMember : Statement {
		std::string name;
		std::vector<ParamStmt*> params;

		EnumMember() { }

		EnumMember(std::string name, std::vector<ParamStmt*> params) :
			name(name), params(params) { }
	};

	struct EnumStmt : Statement {
		std::string name;
		std::vector<EnumMember*> members;

		EnumStmt() { }

		EnumStmt(std::string name, std::vector<EnumMember*> members) :
			name(name), members(members) { }
	};

	struct VarDeclStmt : Statement {
		Type* type;
		std::vector<std::string> bindings;
		Expression* value;

		VarDeclStmt() { }

		VarDeclStmt(Type* type, std::vector<std::string> bindings, Expression* value) :
			type(type), bindings(bindings), value(value) { }
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
		Type* type;
		std::string name;
		GetterStmt* getter;
		SetterStmt* setter;

		PropertyStmt() { }

		PropertyStmt(Type* type, std::string name, GetterStmt* getter, SetterStmt* setter) :
			type(type), name(name), getter(getter), setter(setter) { }
	};

	struct FuncDeclStmt : Statement {
		Type* retType;
		std::string name;
		std::vector<Type*> generics;
		std::vector<TypeConstraint*> constraints;
		std::vector<ParamStmt*> params;

		FuncDeclStmt() { }

		FuncDeclStmt(Type* retType, std::string name, std::vector<Type*> generics,
		             std::vector<TypeConstraint*> constraints, std::vector<ParamStmt*> params) :
			retType(retType), name(name), generics(generics), constraints(constraints),
			params(params) { }
	};

	struct ExternFuncDeclStmt : FuncDeclStmt {
		using FuncDeclStmt::FuncDeclStmt;
	};

	struct InterfaceStmt : Statement {
		std::string name;
		std::vector<FuncDeclStmt*> functions;

		InterfaceStmt() { }

		InterfaceStmt(std::string name, std::vector<FuncDeclStmt*> functions) :
			name(name), functions(functions) { }
	};

	struct ParamStmt : Statement {
		std::string name;
		Type* type;
		Expression* value;

		ParamStmt() { }

		ParamStmt(std::string name, Type* type, Expression* value) :
			name(name), type(type), value(value) { }
	};

	struct ExtendsStmt : Statement {
		NamedType* base;
		BlockExpr* body;

		ExtendsStmt() { }

		ExtendsStmt(NamedType* base, BlockExpr* body) : base(base), body(body) { }
	};

	//
	// Expressions
	//

	struct Expression : Node {
	protected:
		Expression() { }
	};

	struct TupleComponent : Expression {
		std::string name;
		Expression* value;

		TupleComponent() { }

		TupleComponent(std::string name, Expression* value) : name(name), value(value) { }
	};

	struct TupleExpr : Expression {
		std::vector<TupleComponent*> components;

		TupleExpr() { }

		TupleExpr(std::vector<TupleComponent*> components) : components(components) { }
	};

	struct BinaryExpr : Expression {
		Expression* LHS;
		Expression* RHS;
		Operator operation;

		BinaryExpr() { }

		BinaryExpr(Expression* LHS, Operator operation, Expression* RHS) :
			LHS(LHS), operation(operation), RHS(RHS) { }
	};

	struct UnaryExpr : Expression {
		Expression* value;
		OpPosition position;
		Operator operation;

		UnaryExpr() { }

		UnaryExpr(Expression* value, OpPosition position, Operator operation) :
			value(value), position(position), operation(operation) { }
	};

	struct ArrayExpr : Expression {
		std::vector<Expression*> values;

		ArrayExpr() { }

		ArrayExpr(std::vector<Expression*> values) : values(values) { }
	};

	struct ArrayAccessExpr : Expression {
		Expression* LHS;
		Expression* index;

		ArrayAccessExpr() { }

		ArrayAccessExpr(Expression* LHS, Expression* index) : LHS(LHS), index(index) { }
	};

	struct ArrayRangeExpr : Expression {
		Expression* start;
		Expression* end;
		ArrayRangeType type;

		ArrayRangeExpr() { }

		ArrayRangeExpr(Expression* start, Expression* end, ArrayRangeType type) :
			start(start), end(end), type(type) { }
	};

	struct BlockExpr : Expression {
		std::vector<Node*> statements;

		BlockExpr() { }

		BlockExpr(std::vector<Node*> statements) : statements(statements) { }
	};

	struct ConditionalBlock : Expression {
		Expression* condition;
		BlockExpr* body;

		ConditionalBlock() { }

		ConditionalBlock(Expression* condition, BlockExpr* body) :
			condition(condition), body(body) { }
	};

	struct IfExpr : Expression {
		std::vector<ConditionalBlock*> blocks;

		IfExpr() { }

		IfExpr(std::vector<ConditionalBlock*> blocks) : blocks(blocks) { }
	};

	struct LoopExpr : Expression {
		Expression* initializer;
		Expression* condition;
		Expression* afterthought;
		LoopConditionCheck check;

		LoopExpr(Expression* initializer, Expression* condition, Expression* afterthought) :
			initializer(initializer), condition(condition), afterthought(afterthought) { }
	};

	struct StringExpr : Expression {
		std::string value;

		StringExpr() { }

		StringExpr(std::string value) : value(value) { }
	};

	struct VarRefExpr : Expression {
		std::string name;

		VarRefExpr() { }

		VarRefExpr(std::string name) : name(name) { }
	};

	struct IntExpr : Expression {
		int64_t value;

		IntExpr() { }

		IntExpr(int64_t value) : value(value) { }
	};

	struct UIntExpr : Expression {
		uint64_t value;

		UIntExpr() { }

		UIntExpr(uint64_t value) : value(value) { }
	};

	struct DoubleExpr : Expression {
		double value;

		DoubleExpr() { }

		DoubleExpr(double value) : value(value) { }
	};

	struct FloatExpr : Expression {
		float value;

		FloatExpr() { }

		FloatExpr(float value) : value(value) { }
	};

	struct FunctionExpr : Expression {
		Type* retType;
		std::string name;
		std::vector<Type*> generics;
		std::vector<TypeConstraint*> constraints;
		std::vector<ParamStmt*> params;
		BlockExpr* body;

		FunctionExpr() { }

		FunctionExpr(Type* retType, std::string name, std::vector<Type*> generics,
		             std::vector<TypeConstraint*> constraints, std::vector<ParamStmt*> params,
		             BlockExpr* body) : retType(retType), name(name), generics(generics),
		                                constraints(constraints), params(params), body(body) { }
	};

	struct FuncCallExpr : Expression {
		Expression* function;
		std::vector<Expression*> args;

		FuncCallExpr() { }

		FuncCallExpr(Expression* function, std::vector<Expression*> args) :
			function(function), args(args) { }
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
