//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <libast/type.h>
#include <llvm/IR/Type.h>

namespace orange { namespace translate {
	llvm::Type* GetLLVMType(orange::ast::Type* orangeType);
}}