/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

namespace orange { namespace ast {
	struct Expression;

	enum BuiltinTypeKind {
		INT, INT8, INT16, INT32, INT64,
		UINT, UINT8, UINT16, UINT32, UINT64,
		FLOAT, DOUBLE, VAR, VOID, CHAR
	};

	struct Type { };

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
	};

	struct ArrayType : Type {
		Type* base;
		Expression* size;
	};

	struct PointerType : Type {
		Type* base;
	};

	struct ReferenceType : Type {
		Type* base;
	};
}}
