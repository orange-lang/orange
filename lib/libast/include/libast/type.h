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
		INT, UINT,
		INT8, UINT8,
		INT16, UINT16,
		INT32, UINT32,
		INT64, UINT64,
		FLOAT, DOUBLE,
		VAR,
		VOID
	};

	struct Type { };

	struct BuiltinType : Type {
		BuiltinTypeKind kind;
	};

	struct NamedType : Type {
		std::string* name;
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

	enum TypeConstraintKind {
		CLASS, TYPENAME, PROVIDES_DEFAULT
	};

	struct TypeConstraint { };
	struct BasicTypeConstraint : TypeConstraint { TypeConstraintKind kind; };
	struct NamedTypeConstraint : TypeConstraint { std::string* base; };
	struct DataTypeConstraint : TypeConstraint { Type* type; };
}}
