/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/MainFunction.h>
#include <grove/types/Type.h>
#include <llvm/IR/IRBuilder.h>

void MainFunction::setupFunction()
{
	Function::setupFunction();
	
	auto ret_ty = getReturnType()->getLLVMType();
	auto default_ret = llvm::ConstantInt::get(ret_ty, 0, true);
	
	IRBuilder()->CreateStore(default_ret, getRetValue());
}

MainFunction::MainFunction(Module* mod, std::string name)
: Function(mod, name, std::vector<Parameter *>())
{
	// Do nothing
}