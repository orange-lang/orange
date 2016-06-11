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
        int id;
        std::vector<Flag*> flags;

        virtual ~Node() {}
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

    struct Statement : Node { };

    struct PackageStmt : Statement {
        std::string* name;
    };

    struct UsingStmt : Statement {
        std::string* name;
        std::string* alias;
    };

    struct ClassStmt : Statement {
        std::string* name;
        std::vector<NamedType*> implements;
        BlockExpr* body;
    };

    struct EnumMember : Statement {
        std::string* name;
        std::vector<ParamStmt*> params;
    };

    struct EnumStmt : Statement {
        std::string* name;
        std::vector<EnumMember*> members;
    };

    struct VarDeclStmt : Statement {
        Type* type;
        std::vector<std::string*> bindings;
        Expression* value;
    };

    struct GetterStmt : Statement {
        BlockExpr* body;
    };

    struct SetterStmt : Statement {
        BlockExpr* body;
    };

    struct PropertyStmt : Statement {
        Type* type;
        std::string* name;
        GetterStmt* getter;
        SetterStmt* setter;
    };

    struct FuncDeclStmt : Statement {
        Type* retType;
        std::string* name;
        std::vector<Type*> generics;
        std::vector<TypeConstraint*> constraints;
        std::vector<ParamStmt*> params;
    };

    struct ExternFuncDeclStmt : FuncDeclStmt { };

    struct InterfaceStmt : Statement {
        std::string* name;
        std::vector<FuncDeclStmt*> functions;
    };

    struct ParamStmt : Statement {
        std::string* name;
        Type* type;
        Expression* value;
    };

    struct ExtendsStmt : Statement {
        NamedType* base;
        BlockExpr* body;
    };

    //
    // Expressions
    //

    struct Expression : Node { };

    struct TupleComponent : Expression {
        std::string* name;
        Expression* value;
    };

    struct TupleExpr : Expression {
        std::vector<TupleComponent*> components;
    };

    struct BinaryExpr : Expression {
        Expression* LHS;
        Expression* RHS;
        Operator operation;
    };

    struct UnaryExpr : Expression {
        Expression* value;
        OpPosition position;
        Operator operation;
    };

    struct ArrayExpr : Expression {
        std::vector<Expression*> values;
    };

    struct ArrayAccessExpr : Expression {
        Expression* LHS;
        Expression* index;
    };

    struct ArrayRangeExpr : Expression {
        Expression* start;
        Expression* end;
        ArrayRangeType type;
    };

    struct BlockExpr : Expression {
        std::vector<Node*> statements;
    };

    struct ConditionalBlock : Expression {
        Expression* condition;
        BlockExpr* body;
    };

    struct IfExpr : Expression {
        std::vector<ConditionalBlock*> blocks;
    };

    struct LoopExpr : Expression {
        Expression* initializer;
        Expression* condition;
        Expression* afterthought;
        LoopConditionCheck check;
    };

    struct StringExpr : Expression {
        std::string* value;
    };

    struct VarRefExpr : Expression {
        std::string* name;
    };

    struct IntExpr : Expression {
        uint64_t value;
    };

    struct DoubleExpr : Expression {
        double value;
    };

    struct FloatExpr : Expression {
        float value;
    };

    struct FunctionExpr : Expression {
        Type* retType;
        std::string* name;
        std::vector<Type*> generics;
        std::vector<TypeConstraint*> constraints;
        std::vector<ParamStmt*> params;
        BlockExpr* body;
    };

    struct FuncCallExpr : Expression {
        Expression* function;
        std::vector<Expression*> args;
    };
} }
