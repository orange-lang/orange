//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <libast/ast.h>
#include <llvm/IR/Instructions.h>

namespace orange { namespace translate {
	llvm::Instruction::BinaryOps GetLLVMBinOp(orange::ast::BinOp binop, bool fp, bool isSigned);
	bool IsLLVMBinOp(orange::ast::BinOp binop);
	bool IsLLVMAssignOp(orange::ast::BinOp binop);
	bool IsLLVMCompareOp(orange::ast::BinOp binop);
	bool IsLLVMLogicalOp(orange::ast::BinOp binop);
}}

