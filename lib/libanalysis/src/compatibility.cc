//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <map>
#include <libast/typecheck.h>

#include "compatibility.h"

using namespace orange::ast;

static std::map<BuiltinTypeKind, int> BuiltinTypePrecedence = {
	{BuiltinTypeKind::VAR, 14},
	{BuiltinTypeKind::DOUBLE, 13},
	{BuiltinTypeKind::FLOAT, 12},
	{BuiltinTypeKind::INT, 11},
	{BuiltinTypeKind::INT64, 10},
	{BuiltinTypeKind::INT32, 9},
	{BuiltinTypeKind::INT16, 8},
	{BuiltinTypeKind::INT8, 7},
	{BuiltinTypeKind::CHAR, 6},
 	{BuiltinTypeKind::UINT, 5},
	{BuiltinTypeKind::UINT64, 4},
	{BuiltinTypeKind::UINT32, 3},
	{BuiltinTypeKind::UINT16, 2},
	{BuiltinTypeKind::UINT8, 1},
};

bool orange::analysis::AreTypesCompatible(Type* a, Type* b) {
	if (!isA<BuiltinType>(a) || !isA<BuiltinType>(b)) return false;
	
	bool isVoidA = IsVoidType(a);
	bool isVoidB = IsVoidType(b);
	
	// If one of them are voids, they both have to be voids to be compatible.
	if (isVoidA || isVoidB) return isVoidA && isVoidB;
	
	return true;
}

int GetTypePrecedence(Type* a) {
	if (!isA<BuiltinType>(a)) return -1;
	auto it = BuiltinTypePrecedence.find(asA<BuiltinType>(a)->kind);
	if (it == BuiltinTypePrecedence.end()) return -1;
	return it->second;
}

Type* orange::analysis::GetImplicitType(Type* a, Type* b) {
	if (AreTypesCompatible(a, b) == false) return nullptr;

	auto aPrec = GetTypePrecedence(a);
	auto bPrec = GetTypePrecedence(b);

	return aPrec > bPrec ? a : b;
}

