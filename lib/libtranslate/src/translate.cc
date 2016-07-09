//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <iostream>
#include <llvm/IR/LLVMContext.h>

#include <libast/walker.h>
#include <libtranslate/translate.h>

#include "translate_visitor.h"

using namespace orange::ast;
using namespace orange::analysis; 
using namespace orange::translate;

TypeTable* Translator::GetTypeTable() const { 
	return mTypeTable;
}

std::shared_ptr<llvm::Module> Translator::Translate(ast::LongBlockExpr* ast, std::string name) { 
	auto module = std::make_shared<llvm::Module>(name, llvm::getGlobalContext());

	ast::NonTraversalWalker walker;

	TranslateVisitor visitor(walker, module);
	visitor.SetCurrentContext(mTypeTable->GetGlobalContext());

	visitor.VisitLongBlockExpr(ast);

	return module;
}

std::shared_ptr<llvm::Module> Translator::TranslateMain(ast::LongBlockExpr* ast, std::string name) {
	using namespace llvm;

	auto module = std::make_shared<Module>(name, getGlobalContext());

	// Build the main function first
	auto mainTy = llvm::FunctionType::get(IntegerType::get(getGlobalContext(), 32), false);
	auto mainFunction = Function::Create(mainTy, GlobalValue::LinkageTypes::ExternalLinkage, "main", module.get());

	auto body = llvm::BasicBlock::Create(getGlobalContext(), "body", mainFunction);

	ast::NonTraversalWalker walker;

	TranslateVisitor visitor(walker, module);
	visitor.SetCurrentBlock(body);
	visitor.SetCurrentContext(mTypeTable->GetGlobalContext());

	visitor.VisitLongBlockExpr(ast);

	return module;
}

Translator::Translator(analysis::TypeTable* typeInfo) : mTypeTable(typeInfo) { }
