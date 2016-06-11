/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ast.h"
#include "visitor.h"

namespace orange { namespace ast {
	class Walker {
	public:
		/// Dispatches to the proper walk method. Does not visit any nodes.
		void WalkNode(Visitor* visitor, Node* node);
		void WalkStmt(Visitor* visitor, Statement* node);
		void WalkExpr(Visitor* visitor, Expression* node);

		virtual void WalkPackageStmt(Visitor* visitor, PackageStmt* stmt) = 0;
		virtual void WalkUsingStmt(Visitor* visitor, UsingStmt* stmt) = 0;
		virtual void WalkEnumMember(Visitor* visitor, EnumMember* stmt) = 0;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* stmt) = 0;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* stmt) = 0;
		virtual void WalkVarDeclStmt(Visitor* visitor, VarDeclStmt* stmt) = 0;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* stmt) = 0;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* stmt) = 0;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* stmt) = 0;
		virtual void WalkFuncDeclStmt(Visitor* visitor, FuncDeclStmt* stmt) = 0;
		virtual void WalkExternFuncDeclStmt(Visitor* visitor, ExternFuncDeclStmt* stmt) = 0;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* stmt) = 0;
		virtual void WalkParamStmt(Visitor* visitor, ParamStmt* stmt) = 0;
		virtual void WalkExtendsStmt(Visitor* visitor, ExtendsStmt* stmt) = 0;
		virtual void WalkTupleComponent(Visitor* visitor, TupleComponent* expr) = 0;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* expr) = 0;
		virtual void WalkBinaryExpr(Visitor* visitor, BinaryExpr* expr) = 0;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* expr) = 0;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* expr) = 0;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* expr) = 0;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* expr) = 0;
		virtual void WalkBlockExpr(Visitor* visitor, BlockExpr* expr) = 0;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* expr) = 0;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* expr) = 0;
		virtual void WalkLoopExpr(Visitor* visitor, LoopExpr* expr) = 0;
		virtual void WalkStringExpr(Visitor* visitor, StringExpr* expr) = 0;
		virtual void WalkVarRefExpr(Visitor* visitor, VarRefExpr* expr) = 0;
		virtual void WalkIntExpr(Visitor* visitor, IntExpr* expr) = 0;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* expr) = 0;
		virtual void WalkFuncCallExpr(Visitor* visitor, FuncCallExpr* expr) = 0;
		virtual void WalkFloatExpr(Visitor* visitor, FloatExpr* expr) = 0;
		virtual void WalkDoubleExpr(Visitor* visitor, DoubleExpr* expr) = 0;
	};


	/// Walker that will visit concrete elements
	class NonTraversalWalker : public Walker {
	public:
		virtual void WalkPackageStmt(Visitor* visitor, PackageStmt* stmt) override;
		virtual void WalkUsingStmt(Visitor* visitor, UsingStmt* stmt) override;
		virtual void WalkEnumMember(Visitor* visitor, EnumMember* stmt) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* stmt) override;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* stmt) override;
		virtual void WalkVarDeclStmt(Visitor* visitor, VarDeclStmt* stmt) override;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* stmt) override;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* stmt) override;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* stmt) override;
		virtual void WalkFuncDeclStmt(Visitor* visitor, FuncDeclStmt* stmt) override;
		virtual void WalkExternFuncDeclStmt(Visitor* visitor, ExternFuncDeclStmt* stmt) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* stmt) override;
		virtual void WalkParamStmt(Visitor* visitor, ParamStmt* stmt) override;
		virtual void WalkExtendsStmt(Visitor* visitor, ExtendsStmt* stmt) override;
		virtual void WalkTupleComponent(Visitor* visitor, TupleComponent* expr) override;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* expr) override;
		virtual void WalkBinaryExpr(Visitor* visitor, BinaryExpr* expr) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* expr) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* expr) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* expr) override;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* expr) override;
		virtual void WalkBlockExpr(Visitor* visitor, BlockExpr* expr) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* expr) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* expr) override;
		virtual void WalkLoopExpr(Visitor* visitor, LoopExpr* expr) override;
		virtual void WalkStringExpr(Visitor* visitor, StringExpr* expr) override;
		virtual void WalkVarRefExpr(Visitor* visitor, VarRefExpr* expr) override;
		virtual void WalkIntExpr(Visitor* visitor, IntExpr* expr) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* expr) override;
		virtual void WalkFuncCallExpr(Visitor* visitor, FuncCallExpr* expr) override;
		virtual void WalkFloatExpr(Visitor* visitor, FloatExpr* expr) override;
		virtual void WalkDoubleExpr(Visitor* visitor, DoubleExpr* expr) override;
	};

	enum TraversalOrder {
		PREORDER,
		POSTORDER
	};

	// Walker that traverses the hierarchy depth-first.
	class DepthFirstWalker : public Walker {
	private:
		TraversalOrder mOrder;
	public:
		virtual void WalkPackageStmt(Visitor* visitor, PackageStmt* stmt) override;
		virtual void WalkUsingStmt(Visitor* visitor, UsingStmt* stmt) override;
		virtual void WalkEnumMember(Visitor* visitor, EnumMember* stmt) override;
		virtual void WalkClassStmt(Visitor* visitor, ClassStmt* stmt) override;
		virtual void WalkEnumStmt(Visitor* visitor, EnumStmt* stmt) override;
		virtual void WalkVarDeclStmt(Visitor* visitor, VarDeclStmt* stmt) override;
		virtual void WalkPropertyStmt(Visitor* visitor, PropertyStmt* stmt) override;
		virtual void WalkGetterStmt(Visitor* visitor, GetterStmt* stmt) override;
		virtual void WalkSetterStmt(Visitor* visitor, SetterStmt* stmt) override;
		virtual void WalkFuncDeclStmt(Visitor* visitor, FuncDeclStmt* stmt) override;
		virtual void WalkExternFuncDeclStmt(Visitor* visitor, ExternFuncDeclStmt* stmt) override;
		virtual void WalkInterfaceStmt(Visitor* visitor, InterfaceStmt* stmt) override;
		virtual void WalkParamStmt(Visitor* visitor, ParamStmt* stmt) override;
		virtual void WalkExtendsStmt(Visitor* visitor, ExtendsStmt* stmt) override;
		virtual void WalkTupleComponent(Visitor* visitor, TupleComponent* expr) override;
		virtual void WalkTupleExpr(Visitor* visitor, TupleExpr* expr) override;
		virtual void WalkBinaryExpr(Visitor* visitor, BinaryExpr* expr) override;
		virtual void WalkUnaryExpr(Visitor* visitor, UnaryExpr* expr) override;
		virtual void WalkArrayExpr(Visitor* visitor, ArrayExpr* expr) override;
		virtual void WalkArrayAccessExpr(Visitor* visitor, ArrayAccessExpr* expr) override;
		virtual void WalkArrayRangeExpr(Visitor* visitor, ArrayRangeExpr* expr) override;
		virtual void WalkBlockExpr(Visitor* visitor, BlockExpr* expr) override;
		virtual void WalkConditionalBlock(Visitor* visitor, ConditionalBlock* expr) override;
		virtual void WalkIfExpr(Visitor* visitor, IfExpr* expr) override;
		virtual void WalkLoopExpr(Visitor* visitor, LoopExpr* expr) override;
		virtual void WalkStringExpr(Visitor* visitor, StringExpr* expr) override;
		virtual void WalkVarRefExpr(Visitor* visitor, VarRefExpr* expr) override;
		virtual void WalkIntExpr(Visitor* visitor, IntExpr* expr) override;
		virtual void WalkFunctionExpr(Visitor* visitor, FunctionExpr* expr) override;
		virtual void WalkFuncCallExpr(Visitor* visitor, FuncCallExpr* expr) override;
		virtual void WalkFloatExpr(Visitor* visitor, FloatExpr* expr) override;
		virtual void WalkDoubleExpr(Visitor* visitor, DoubleExpr* expr) override;

		DepthFirstWalker(TraversalOrder order);
	};
}}
