//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <iostream>
#include <llvm/IR/LLVMContext.h>

#include <libtranslate/translate.h>

using namespace orange::ast;
using namespace orange::analysis; 
using namespace orange::translate;

TypeTable* Translator::GetTypeTable() const { 
	return mTypeTable;
}

std::shared_ptr<llvm::Module> Translator::Translate(ast::LongBlockExpr* ast, std::string name) { 
	auto module = std::make_shared<llvm::Module>(name, llvm::getGlobalContext());
	return module;
}

std::shared_ptr<llvm::Module> Translator::TranslateMain(ast::LongBlockExpr* ast, std::string name) { 
	auto module = std::make_shared<llvm::Module>(name, llvm::getGlobalContext());
	return module;
}

Translator::Translator(analysis::TypeTable* typeInfo) : mTypeTable(typeInfo) { }
