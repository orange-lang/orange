//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/typecheck.h>

using namespace orange::ast;

bool IsIntegerType(Type* type) {
	if (isA<BuiltinType>(type)) {
		auto ty = asA<BuiltinType>(type);
		return ty->kind == INT || ty->kind == INT8 || ty->kind == INT16 || ty->kind == INT32 || ty->kind == INT64 ||
			ty->kind == UINT || ty->kind == UINT8 || ty->kind == UINT16 || ty->kind == UINT32 || ty->kind == UINT64;
	} else if (isA<ArrayType>(type)) {
		return IsIntegerType(asA<ArrayType>(type)->base);
	}
	
	return false;
}

bool IsSignedType(Type* type) {
	if (isA<BuiltinType>(type)) {
		auto ty = asA<BuiltinType>(type);
		return ty->kind == INT || ty->kind == INT8 || ty->kind == INT16 || ty->kind == INT32 || ty->kind == INT64;
	} else if (isA<ArrayType>(type)) {
		return IsSignedType(asA<ArrayType>(type)->base);
	}
	
	return false;
}

bool IsFloatingPointType(Type* type) {
	if (isA<BuiltinType>(type)) {
		auto ty = asA<BuiltinType>(type);
		return ty->kind == FLOAT || ty->kind == DOUBLE;
	} else if (isA<ArrayType>(type)) {
		return IsFloatingPointType(asA<ArrayType>(type)->base);
	}
	
	return false;
}

bool IsBooleanType(Type* type) {
	if (isA<BuiltinType>(type)) {
		auto ty = asA<BuiltinType>(type);
		return ty->kind == BuiltinTypeKind::BOOL;
	}
	
	return false;
}

bool IsVoidType(orange::ast::Type* type) {
	if (isA<BuiltinType>(type)) {
		return asA<BuiltinType>(type)->kind == VOID;
	}

	return false;
}

int GetIntegerBitWidth(Type* type) {
	if (isA<BuiltinType>(type)) {
		auto ty = asA<BuiltinType>(type);
		switch (ty->kind) {
			case INT: case UINT: case INT64: case UINT64: return 64;
			case INT32: case UINT32: return 32;
			case INT16: case UINT16: return 16;
			case INT8: case UINT8: return 8;
			default: return -1;
		}
	} else if (isA<ArrayType>(type)) {
		return IsIntegerType(asA<ArrayType>(type)->base);
	}

	return -1;
}

bool IsGenericType(orange::ast::Type* type) {
	if (isA<BuiltinType>(type)) {
		return asA<BuiltinType>(type)->kind == VAR;
	} else if (isA<AccessType>(type)) {
		auto _ty = asA<AccessType>(type);
		return IsGenericType(_ty->LHS) || IsGenericType(_ty->RHS);
	} else if (isA<IdentifierType>(type)) {
		// TODO: this is rough; we will probably need the default context for this one.
		return true;
	} else if (isA<ArrayType>(type)) {
		// TODO: is size generic?
		return IsGenericType(asA<ArrayType>(type)->base);
	} else if (isA<PointerType>(type)) {
		return IsGenericType(asA<PointerType>(type)->base);
	} else if (isA<FunctionType>(type)) {
		auto _ty = asA<FunctionType>(type);
		if (IsGenericType(_ty->returnType)) return true;
		for (auto type : _ty->params) {
			if (IsGenericType(type)) return true;
		}
	}
	
	return false;
}

bool IsLValue(orange::ast::Node* node, orange::ast::Type* nodeType) {
	// TODO: this isn't complete.
	if (isA<Identifier>(node)) return true;
	
	return false;
}
