//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/typecheck.h>
#include <stdexcept>

#include "type_converter.h"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/DerivedTypes.h>

using namespace orange::ast;

llvm::Type* orange::translate::GetLLVMType(Type* orangeType) {
	if (IsIntegerType(orangeType)) {
		int width = GetIntegerBitWidth(orangeType);
		return llvm::Type::getIntNTy(llvm::getGlobalContext(), width);
	} else if (isA<BuiltinType>(orangeType)) {
		auto builtin = asA<BuiltinType>(orangeType);
		if (builtin->kind == BuiltinTypeKind::FLOAT)  return llvm::Type::getFloatTy(llvm::getGlobalContext());
		if (builtin->kind == BuiltinTypeKind::DOUBLE) return llvm::Type::getDoubleTy(llvm::getGlobalContext());
		if (builtin->kind == BuiltinTypeKind::BOOL) return llvm::Type::getInt1Ty(llvm::getGlobalContext());
	}

	throw std::runtime_error("Don't know how to convert Orange type to LLVM type");
}

