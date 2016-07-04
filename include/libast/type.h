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

namespace orange { namespace ast {
	struct Expression;
	struct Identifier;

	enum BuiltinTypeKind {
		INT, INT8, INT16, INT32, INT64,
		UINT, UINT8, UINT16, UINT32, UINT64,
		FLOAT, DOUBLE, VAR, VOID, CHAR
	};

	struct Type {
	public:
		virtual ~Type() {}
	};

	struct AccessType : Type {
		Type* LHS;
		Type* RHS;

		AccessType() { }
		AccessType(Type* LHS, Type* RHS) : LHS(LHS), RHS(RHS) { }
	};

	struct IdentifierType : Type {
		Identifier* id;

		IdentifierType() { }
		IdentifierType(Identifier* id) : id(id) { }
	};

	struct BuiltinType : Type {
		BuiltinTypeKind kind;

		BuiltinType() { }
		BuiltinType(BuiltinTypeKind kind) : kind(kind) { }
	};

	struct ArrayType : Type {
		Type* base;
		Expression* size;

		ArrayType() { }
		ArrayType(Type* base, Expression* size) : base(base), size(size) { }
	};

	struct PointerType : Type {
		Type* base;

		PointerType() { }
		PointerType(Type* base) : base(base) { }
	};

	struct ReferenceType : Type {
		Type* base;

		ReferenceType() { }
		ReferenceType(Type* base) : base(base) { }
	};

	struct TupleType : Type {
		std::vector<Type*> types;

		TupleType() { }
		TupleType(std::vector<Type*> types) : types(types) { }
	};

	struct FunctionType : Type {
		std::vector<Type*> params;
		Type* returnType;

		FunctionType() { }
		FunctionType(std::vector<Type*> params, Type* returnType) :
			params(params), returnType(returnType) { }
	};

	// Define basic builtin types
#define DEFINE_BUILTIN(name, val) \
	struct name : BuiltinType { name() : BuiltinType(val) { } }

	DEFINE_BUILTIN(IntType, BuiltinTypeKind::INT);
	DEFINE_BUILTIN(Int8Type, BuiltinTypeKind::INT8);
	DEFINE_BUILTIN(Int16Type, BuiltinTypeKind::INT16);
	DEFINE_BUILTIN(Int32Type, BuiltinTypeKind::INT32);
	DEFINE_BUILTIN(Int64Type, BuiltinTypeKind::INT64);

	DEFINE_BUILTIN(UIntType, BuiltinTypeKind::UINT);
	DEFINE_BUILTIN(UInt8Type, BuiltinTypeKind::UINT8);
	DEFINE_BUILTIN(UInt16Type, BuiltinTypeKind::UINT16);
	DEFINE_BUILTIN(UInt32Type, BuiltinTypeKind::UINT32);
	DEFINE_BUILTIN(UInt64Type, BuiltinTypeKind::UINT64);

	DEFINE_BUILTIN(FloatType, BuiltinTypeKind::FLOAT);
	DEFINE_BUILTIN(DoubleType, BuiltinTypeKind::DOUBLE);

	DEFINE_BUILTIN(CharType, BuiltinTypeKind::CHAR);

	struct StringType : PointerType {
		StringType() : PointerType(new CharType) { }
	};
}}
