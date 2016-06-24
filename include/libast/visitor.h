/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ast.h"

namespace orange { namespace ast {
	class Visitor {
	public:
		virtual void VisitPackageStmt(PackageStmt* stmt) { }

		virtual void VisitUsingStmt(UsingStmt* stmt) { }

		virtual void VisitEnumMember(EnumMember* stmt) { }

		virtual void VisitClassStmt(ClassStmt* stmt) { }

		virtual void VisitEnumStmt(EnumStmt* stmt) { }

		virtual void VisitVarDeclStmt(VarDeclStmt* stmt) { }

		virtual void VisitPropertyStmt(PropertyStmt* stmt) { }

		virtual void VisitGetterStmt(GetterStmt* stmt) { }

		virtual void VisitSetterStmt(SetterStmt* stmt) { }

		virtual void VisitFuncDeclStmt(FuncDeclStmt* stmt) { }

		virtual void VisitExternFuncDeclStmt(ExternFuncDeclStmt* stmt) { }

		virtual void VisitInterfaceStmt(InterfaceStmt* stmt) { }

		virtual void VisitParamStmt(ParamStmt* stmt) { }

		virtual void VisitExtendsStmt(ExtendsStmt* stmt) { }

		virtual void VisitTupleComponent(TupleComponent* expr) { }

		virtual void VisitTupleExpr(TupleExpr* expr) { }

		virtual void VisitBinaryExpr(BinaryExpr* expr) { }

		virtual void VisitUnaryExpr(UnaryExpr* expr) { }

		virtual void VisitArrayExpr(ArrayExpr* expr) { }

		virtual void VisitArrayAccessExpr(ArrayAccessExpr* expr) { }

		virtual void VisitArrayRangeExpr(ArrayRangeExpr* expr) { }

		virtual void VisitBlockExpr(BlockExpr* expr) { }

		virtual void VisitConditionalBlock(ConditionalBlock* expr) { }

		virtual void VisitIfExpr(IfExpr* expr) { }

		virtual void VisitLoopExpr(LoopExpr* expr) { }

		virtual void VisitStringExpr(StringExpr* expr) { }

		virtual void VisitVarRefExpr(VarRefExpr* expr) { }

		virtual void VisitIntExpr(IntExpr* expr) { }

		virtual void VisitUIntExpr(UIntExpr* expr) { }

		virtual void VisitFunctionExpr(FunctionExpr* expr) { }

		virtual void VisitFuncCallExpr(FuncCallExpr* expr) { }

		virtual void VisitFloatExpr(FloatExpr* expr) { }

		virtual void VisitDoubleExpr(DoubleExpr* expr) { }
	};
}}
