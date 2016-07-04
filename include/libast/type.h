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
}}
