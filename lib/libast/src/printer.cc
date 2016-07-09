//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <sstream>
#include <stdexcept>
#include <map>

#include <libast/walker.h>
#include <libast/printer.h>
#include <libast/typecheck.h>
#include <libast/type.h>

namespace orange { namespace ast {
	static std::map<BinOp, std::string> BinOpNames = {
		{ADD, "ADD"}, {SUBTRACT, "SUBTRACT"}, {DIVIDE, "DIVIDE"}, {MULTIPLY, "MULTIPLY"},
		{REMAINDER, "REMAINDER"}, {BIT_OR, "BIT_OR"}, {BIT_AND, "BIT_AND"}, {BIT_XOR, "BIT_XOR"},
		{SHIFT_LEFT, "SHIFT_LEFT"}, {SHIFT_RIGHT, "SHIFT_RIGHT"}, {ASSIGN, "ASSIGN"}, {EQUALS, "EQUALS"},
		{PLUS_ASSIGN, "PLUS_ASSIGN"}, {MINUS_ASSIGN, "MINUS_ASSIGN"}, {TIMES_ASSIGN, "TIMES_ASSIGN"},
		{DIVIDE_ASSIGN, "DIVIDE_ASSIGN"}, {REMAINDER_ASSIGN, "REMAINDER_ASSIGN"},
		{SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN"}, {SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN"},
		{BIT_OR_ASSIGN, "BIT_OR_ASSIGN"}, {BIT_AND_ASSIGN, "BIT_AND_ASSIGN"}, {BIT_XOR_ASSIGN, "BIT_XOR_ASSIGN"},
		{LESS_THAN, "LESS_THAN"}, {GREATER_THAN, "GREATER_THAN"}, {LEQ, "LEQ"}, {GEQ, "GEQ"},
		{NEQ, "NEQ"}, {AND, "AND"}, {OR, "OR"}
	};

	static std::map<UnaryOp, std::string> UnaryOpNames = {
		{INCREMENT, "INCREMENT"}, {DECREMENT, "DECREMENT"}, {MINUS, "MINUS"},
		{NOT, "NOT"}, {TILDE, "TILDE"}, {TIMES, "TIMES"}, {REFERENCE,"REFERENCE"},
	};

	static std::map<UnaryOrder, std::string> UnaryOrderNames = {
		{PREFIX, "PREFIX"}, {POSTFIX, "POSTFIX"}
	};

	std::ostream& operator<<(std::ostream& os, const BinOp& tok) {
		auto it = BinOpNames.find(tok);
		if (it == BinOpNames.end()) return os << tok;
		return os << it->second;
	}

	std::ostream& operator<<(std::ostream& os, const UnaryOp& tok) {
		auto it = UnaryOpNames.find(tok);
		if (it == UnaryOpNames.end()) return os << tok;
		return os << it->second;
	}

	std::ostream& operator<<(std::ostream& os, const UnaryOrder& tok) {
		auto it = UnaryOrderNames.find(tok);
		if (it == UnaryOrderNames.end()) return os << tok;
		return os << it->second;
	}
}}

using namespace orange::ast;

void ASTPrinter::PrintType(Type* ty) {
	if (isA<AccessType>(ty)) {
		auto at = asA<AccessType>(ty);
		PrintType(at->LHS);
		mOutput << ".";
		PrintType(at->RHS);
	} else if (isA<IdentifierType>(ty)) {
		mOutput << "(" << std::endl;
		mIndentation++;
		mWalker.WalkIdentifier(this, asA<IdentifierType>(ty)->id);
		mIndentation--;
		handleIdententation();
		mOutput << std::endl << ")";
	} else if (isA<BuiltinType>(ty)) {
		switch (asA<BuiltinType>(ty)->kind) {
			case INT: mOutput << "int"; break;
			case INT8: mOutput << "int8"; break;
			case INT16: mOutput << "int16"; break;
			case INT32: mOutput << "int32"; break;
			case INT64: mOutput << "int64"; break;
			case UINT: mOutput << "uint"; break;
			case UINT8: mOutput << "uint8"; break;
			case UINT16: mOutput << "uint16"; break;
			case UINT32: mOutput << "uint32"; break;
			case UINT64: mOutput << "uint64"; break;
			case FLOAT: mOutput << "float"; break;
			case DOUBLE: mOutput << "double"; break;
			case VAR: mOutput << "var"; break;
			case VOID: mOutput << "void"; break;
			case CHAR: mOutput << "char"; break;
			default: throw std::runtime_error("Unknown builtin type");
		}
	} else if (isA<ArrayType>(ty)) {
		PrintType(asA<ArrayType>(ty)->base);
		mOutput << "[" << std::endl;
		mIndentation++;
		mWalker.WalkExpr(this, asA<ArrayType>(ty)->size);
		mIndentation--;
		handleIdententation();
		mOutput << std::endl << "]";
	} else if (isA<PointerType>(ty)) {
		PrintType(asA<PointerType>(ty)->base);
		mOutput << "*";
	} else if (isA<ReferenceType>(ty)) {
		PrintType(asA<ReferenceType>(ty)->base);
		mOutput << "&";
	} else if (isA<TupleType>(ty)) {
		mOutput << "(";

		for (auto innerTy : asA<TupleType>(ty)->types) {
			PrintType(innerTy);
			mOutput << ",";
		}

		mOutput << ")";
	} else if (isA<FunctionType>(ty)) {
		mOutput << "(";

		auto fnTy = asA<FunctionType>(ty);
		for (unsigned long i = 0; i < fnTy->params.size(); i++) {
			PrintType(fnTy->params[i]);
			if (i + 1 < fnTy->params.size()) mOutput << ",";
		}

		mOutput << ")";

		if (fnTy->returnType != nullptr) {
			mOutput << " -> ";
			PrintType(fnTy->returnType);
		}
	}
}


std::string ASTPrinter::getOutput() const {
	return mOutput.str();
}

void ASTPrinter::handleIdententation() {
	for (int i = 0; i < mIndentation; i++) mOutput << "\t";
}

void ASTPrinter::printID(Node* node) { }


void ASTPrinter::VisitCommentStmt(CommentStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "CommentStmt(";
	mOutput << "value = " << node->value;
	mOutput << ")";
}

void ASTPrinter::VisitLoopStmt(LoopStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "LoopStmt(";
	mOutput << "check = " << node->check;
	mOutput << "):" << std::endl;

	mIndentation++;

	if (node->initializer) {
		mWalker.WalkExpr(this, node->initializer);
		mOutput << std::endl;
	}

	if (node->condition) {
		mWalker.WalkExpr(this, node->condition);
		mOutput << std::endl;
	}

	if (node->afterthought) {
		mWalker.WalkExpr(this, node->afterthought);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitForeachStmt(ForeachStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ForeachStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkExpr(this, node->declaration);
	mOutput << std::endl;

	mWalker.WalkExpr(this, node->value);
	mOutput << std::endl;

	mWalker.WalkExpr(this, node->body);
	mOutput << std::endl;

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitBreakStmt(BreakStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "BreakStmt()";
}

void ASTPrinter::VisitContinueStmt(ContinueStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ContinueStmt()";
}

void ASTPrinter::VisitYieldStmt(YieldStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "YieldStmt():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->value);

	mIndentation--;
}

void ASTPrinter::VisitReturnStmt(ReturnStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ReturnStmt()";

	mIndentation++;

	if (node->value != nullptr) {
		mOutput << std::endl;
		mWalker.WalkExpr(this, node->value);
	}

	mIndentation--;
}

void ASTPrinter::VisitAggregateStmt(AggregateStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "AggregateStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkBlockExpr(this, node->body);
	mIndentation--;
}

void ASTPrinter::VisitExternFuncStmt(ExternFuncStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ExternFuncStmt(";
	mOutput << "retType = ";
	PrintType(node->retType);
    mOutput << "):" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;

	for (auto param : node->params) {
		mWalker.WalkVarDeclExpr(this, param);
		mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitEnumValue(EnumValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "EnumValue():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);

	if (node->params.size() > 0) mOutput << std::endl;

	for (unsigned long i = 0; i < node->params.size(); i++) {
		mWalker.WalkVarDeclExpr(this, node->params[i]);
		if (i + 1 < node->params.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitEnumStmt(EnumStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "EnumStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);

	if (node->values.size() > 0) mOutput << std::endl;

	for (unsigned long i = 0; i < node->values.size(); i++) {
		mWalker.WalkEnumValue(this, node->values[i]);
		if (i + 1 < node->values.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitClassStmt(ClassStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ClassStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;

	for (auto super : node->supers) {
		mWalker.WalkIdentifier(this, super);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitInterfaceStmt(InterfaceStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "InterfaceStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitExtendStmt(ExtendStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ExtendStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;

	for (auto super : node->supers) {
		mWalker.WalkIdentifier(this, super);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitNamespaceStmt(NamespaceStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "NamespaceStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);

	if (node->body != nullptr) {
		mOutput << "\n";
		mWalker.WalkBlockExpr(this, node->body);
	}

	mIndentation--;
}

void ASTPrinter::VisitImportStmt(ImportStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ImportStmt():" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);

	mIndentation--;
}

void ASTPrinter::VisitGetterStmt(GetterStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "GetterStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkBlockExpr(this, node->body);
	mIndentation--;
}

void ASTPrinter::VisitSetterStmt(SetterStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "SetterStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkBlockExpr(this, node->body);
	mIndentation--;
}

void ASTPrinter::VisitPropertyStmt(PropertyStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "PropertyStmt(";
	if (node->type != nullptr) {
		mOutput << "type = ";
		PrintType(node->type);
	}
	mOutput << "):" << std::endl;

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;

	mWalker.WalkBlockExpr(this, node->body);

	mIndentation--;
}

void ASTPrinter::VisitThrowStmt(ThrowStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ThrowStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkExpr(this, node->exception);
	mIndentation--;
}

void ASTPrinter::VisitDeleteStmt(DeleteStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "DeleteStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkExpr(this, node->deallocation);
	mIndentation--;
}

void ASTPrinter::VisitExprStmt(ExprStmt* node) {
	handleIdententation();
	printID(node);

	mOutput << "ExprStmt():" << std::endl;

	mIndentation++;
	mWalker.WalkExpr(this, node->expression);
	mIndentation--;
}

void ASTPrinter::VisitVarDeclExpr(VarDeclExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "VarDeclExpr(";
	if (node->types.size() > 0) {
		mOutput << "types: [";
		for (unsigned long i = 0; i < node->types.size(); i++) {
			PrintType(node->types[i]);

			if (i + 1 < node->types.size()) mOutput << ", ";
		}
		mOutput << "]";
	}
	mOutput << "):" << std::endl;

	mIndentation++;

	for (unsigned long i = 0; i < node->bindings.size(); i++) {
		mWalker.WalkIdentifier(this, node->bindings[i]);
		if (i + 1 < node->bindings.size()) mOutput << std::endl;
	}

	if (node->value) mWalker.WalkExpr(this, node->value);

	mIndentation--;
}

void ASTPrinter::VisitIntValue(IntValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "IntValue(";
	mOutput << "value = " << node->value;
	mOutput << ", type = ";
	PrintType(node->type);
	mOutput << ")";
}

void ASTPrinter::VisitUIntValue(UIntValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "UIntValue(";
	mOutput << "value = " << node->value;
	mOutput << ", type = ";
	PrintType(node->type);
	mOutput << ")";
}

void ASTPrinter::VisitFloatValue(FloatValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "FloatValue(";
	mOutput << "value = " << node->value;
	mOutput << ")";
}

void ASTPrinter::VisitDoubleValue(DoubleValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "DoubleValue(";
	mOutput << "value = " << node->value;
	mOutput << ")";
}

void ASTPrinter::VisitStringValue(StringValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "StringValue(";
	mOutput << "value = \"" << node->value;
	mOutput << "\")";
}

void ASTPrinter::VisitCharValue(CharValue* node) {
	handleIdententation();
	printID(node);

	mOutput << "CharValue(";
	mOutput << "value = '" << (char)node->value;
	mOutput << "')";
}

void ASTPrinter::VisitThisID(ThisID* node) {
	handleIdententation();
	printID(node);

	mOutput << "ThisID()";
}

void ASTPrinter::VisitReferenceIDExpr(ReferenceIDExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "ReferenceIDExpr(";
	mOutput << "name = \"" << node->name << "\"";
	mOutput << ")";
}

void ASTPrinter::VisitNamedIDExpr(NamedIDExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "NamedIDExpr(";
	mOutput << "name = \"" << node->name << "\"";
	mOutput << ")";
}

void ASTPrinter::VisitTempIDExpr(TempIDExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "TempIDExpr()";
}

void ASTPrinter::VisitDtorIDExpr(DtorIDExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "DtorIDExpr():" << std::endl;

	mIndentation++;
	mWalker.WalkIdentifier(this, node->base);
	mIndentation--;
}

void ASTPrinter::VisitAccessIDExpr(AccessIDExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "AccessIDExpr():" << std::endl;

	mIndentation++;
	mWalker.WalkIdentifier(this, node->LHS);
	mOutput << std::endl;
	mWalker.WalkIdentifier(this, node->RHS);
	mIndentation--;
}

void ASTPrinter::VisitLongBlockExpr(LongBlockExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "LongBlockExpr():";

	mIndentation++;

	if (node->statements.size() > 0) mOutput << "\n";

	for (int i = 0; i < node->statements.size(); i++) {
		auto stmt = node->statements[i];

		mWalker.WalkNode(this, stmt);

		if (i + 1 < node->statements.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitShortBlockExpr(ShortBlockExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "ShortBlockExpr():\n";

	mIndentation++;
	mWalker.WalkNode(this, node->statement);
	mIndentation--;
}

void ASTPrinter::VisitBinOpExpr(BinOpExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "BinOpExpr(";
	mOutput << "op: " << node->op;
	mOutput << "):\n";

	mIndentation++;
	mWalker.WalkExpr(this, node->LHS);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->RHS);
	mIndentation--;
}

void ASTPrinter::VisitUnaryExpr(UnaryExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "UnaryExpr(";
	mOutput << "op: " << node->op;
	mOutput << "order: " << node->order;
	mOutput << "):\n";

	mIndentation++;
	mWalker.WalkExpr(this, node->LHS);
	mIndentation--;
}

void ASTPrinter::VisitTupleExpr(TupleExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "TupleExpr():\n";

	mIndentation++;

	for (unsigned long i = 0; i < node->values.size(); i++) {
		mWalker.WalkExpr(this, node->values[i]);
		if (i + 1 < node->values.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitArrayExpr(ArrayExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "ArrayExpr():\n";

	mIndentation++;

	for (unsigned long i = 0; i < node->values.size(); i++) {
		mWalker.WalkExpr(this, node->values[i]);
		if (i + 1 < node->values.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitArrayRangeExpr(ArrayRangeExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "ArrayRangeExpr(";
	mOutput << "type = " << node->type;
	mOutput << "):\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->LHS);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->RHS);

	mIndentation--;
}

void ASTPrinter::VisitArrayAccessExpr(ArrayAccessExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "ArrayAccessExpr():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->expression);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->index);

	mIndentation--;
}

void ASTPrinter::VisitMemberAccessExpr(MemberAccessExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "MemberAccessExpr():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->LHS);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->RHS);

	mIndentation--;
}

void ASTPrinter::VisitNamedExpr(NamedExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "NamedExpr():\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->name);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->value);

	mIndentation--;
}

void ASTPrinter::VisitConditionalBlock(ConditionalBlock* node) {
	handleIdententation();
	printID(node);

	mOutput << "ConditionalBlock():\n";

	mIndentation++;

	if (node->condition != nullptr) {
		mWalker.WalkExpr(this, node->condition);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->block);

	mIndentation--;
}

void ASTPrinter::VisitIfExpr(IfExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "IfExpr():\n";

	mIndentation++;

	for (unsigned long i = 0; i < node->blocks.size(); i++) {
		mWalker.WalkConditionalBlock(this, node->blocks[i]);
		if (i + 1 < node->blocks.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitTernaryExpr(TernaryExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "TernaryExpr():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->condition);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->trueValue);
	mOutput << std::endl;
	mWalker.WalkExpr(this, node->falseValue);

	mIndentation--;
}

void ASTPrinter::VisitSwitchPattern(SwitchPattern* node) {
	handleIdententation();
	printID(node);

	mOutput << "SwitchPattern():\n";

	mIndentation++;

	for (auto pattern : node->patterns) {
		mWalker.WalkExpr(this, pattern);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->block);

	mIndentation--;
}

void ASTPrinter::VisitSwitchExpr(SwitchExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "SwitchExpr():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->condition);
	if (node->patterns.size() > 0) mOutput << std::endl;

	for (unsigned long i = 0; i < node->patterns.size(); i++) {
		mWalker.WalkSwitchPattern(this, node->patterns[i]);
		if (i + 1 < node->patterns.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitClassConstraint(ClassConstraint* node) {
	handleIdententation();
	printID(node);

	mOutput << "ClassConstraint():\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->identifier);

	mIndentation--;
}

void ASTPrinter::VisitDefaultCtorConstraint(DefaultCtorConstraint* node) {
	handleIdententation();
	printID(node);

	mOutput << "DefaultCtorConstraint():\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->identifier);

	mIndentation--;
}

void ASTPrinter::VisitBaseConstraint(BaseConstraint* node) {
	handleIdententation();
	printID(node);

	mOutput << "BaseConstraint():\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->identifier);
	mWalker.WalkIdentifier(this, node->base);

	mIndentation--;
}

void ASTPrinter::VisitDataConstraint(DataConstraint* node) {
	handleIdententation();
	printID(node);

	mOutput << "DataConstraint(";
	mOutput << "dataType: ";
	PrintType(node->dataType);
	mOutput << "):\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->identifier);

	mIndentation--;
}

void ASTPrinter::VisitTypeConstraint(TypeConstraint* node) {
	handleIdententation();
	printID(node);

	mOutput << "TypeConstraint(";
	mOutput << "dataType: ";
	PrintType(node->type);
	mOutput << "):\n";

	mIndentation++;

	mWalker.WalkIdentifier(this, node->identifier);

	mIndentation--;
}

void ASTPrinter::VisitGenerics(Generics* node) {
	handleIdententation();
	printID(node);

	mOutput << "Generics():\n";

	mIndentation++;

	for (unsigned long i = 0; i < node->genericTypes.size(); i++) {
		mWalker.WalkIdentifier(this, node->genericTypes[i]);
		if (i + 1 < node->genericTypes.size()) mOutput << std::endl;
	}

	if (node->constraints.size() > 0) mOutput << std::endl;

	for (unsigned long i = 0; i < node->constraints.size(); i++) {
		mWalker.WalkConstraint(this, node->constraints[i]);
		if (i + 1 < node->constraints.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitFunctionExpr(FunctionExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "FunctionExpr(";
	if (node->retType != nullptr) {
		mOutput << "retType: ";
		PrintType(node->retType);
	}
	mOutput << "):\n";

	mIndentation++;

	if (node->name != nullptr) mWalker.WalkIdentifier(this, node->name);
	if (node->name != nullptr && node->generics != nullptr) mOutput << std::endl;
	if (node->generics != nullptr) mWalker.WalkGenerics(this, node->generics);

	mOutput << std::endl;

	for (auto param : node->params) {
		mWalker.WalkVarDeclExpr(this, param);
		mOutput << std::endl;
	}

	mWalker.WalkBlockExpr(this, node->block);

	mIndentation--;
}

void ASTPrinter::VisitCatchBlock(CatchBlock* node) {
	handleIdententation();
	printID(node);

	mOutput << "CatchBlock():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->exception);
	mOutput << std::endl;
	mWalker.WalkBlockExpr(this, node->block);

	mIndentation--;
}

void ASTPrinter::VisitTryExpr(TryExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "TryExpr():\n";

	mIndentation++;

	mWalker.WalkBlockExpr(this, node->block);
	mOutput << std::endl;

	for (unsigned long i = 0; i < node->catches.size(); i++) {
		mWalker.WalkCatchBlock(this, node->catches[i]);
		if (i + 1 < node->catches.size()) mOutput << std::endl;
	}

	if (node->finally != nullptr) {
		mOutput << std::endl;
		mWalker.WalkBlockExpr(this, node->finally);
	}

	mIndentation--;
}

void ASTPrinter::VisitCastExpr(CastExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "CastExpr(";
	mOutput << "targetType: ";
	PrintType(node->targetType);
	mOutput << "):\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->expr);

	mIndentation--;
}

void ASTPrinter::VisitFunctionCallExpr(FunctionCallExpr* node) {
	handleIdententation();
	printID(node);

	mOutput << "FunctionCallExpr():\n";

	mIndentation++;

	mWalker.WalkExpr(this, node->function);
	if (node->args.size() > 0) mOutput << std::endl;

	for (unsigned long i = 0; i < node->args.size(); i++) {
		mWalker.WalkExpr(this, node->args[i]);
		if (i + 1 < node->args.size()) mOutput << std::endl;
	}

	mIndentation--;
}

void ASTPrinter::VisitNewExpr(NewExpr* node) {
	mOutput << "NewExpr():\n";

	mIndentation++;
	mWalker.WalkExpr(this, node->allocation);
	mIndentation--;
}

ASTPrinter::ASTPrinter(Walker& walker) : mWalker(walker) { }

std::string orange::ast::PrettyPrint(LongBlockExpr* ast) {
	NonTraversalWalker walker;

	ASTPrinter visitor(walker);
	walker.WalkNode(&visitor, ast);

	return visitor.getOutput();
}