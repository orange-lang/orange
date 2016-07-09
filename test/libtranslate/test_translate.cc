//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <gtest/gtest.h>
#include <map>

#include <libtranslate/translate.h>
#include <libanalysis/analyze.h>
#include <libast/ast.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

#include <libast/visitor.h>
#include <libast/walker.h>

#include "translate_visitor.h"

using namespace orange::ast;
using namespace orange::translate;
using namespace orange::analysis;

using namespace llvm;

std::shared_ptr<llvm::Module> CompileAST(LongBlockExpr* ast) {
	std::vector<LongBlockExpr *> astList = { ast };
	TypeResolution tr(astList);

	auto tt = tr.GenerateTypeTable();
	Translator t(tt);

	return t.TranslateMain(ast, "main.or");
}

llvm::Value* CompileValueForNode(Node* node) {
	LongBlockExpr ast (std::vector<Node*>({ node }));
	std::vector<LongBlockExpr *> astList = { &ast };
	TypeResolution tr(astList);

	auto module = std::make_shared<Module>("main.or", getGlobalContext());

	// Build the main function first
	auto mainTy = llvm::FunctionType::get(IntegerType::get(getGlobalContext(), 32), false);
	auto mainFunction = Function::Create(mainTy, GlobalValue::LinkageTypes::ExternalLinkage, "main", module.get());

	auto body = llvm::BasicBlock::Create(getGlobalContext(), "body", mainFunction);

	orange::ast::NonTraversalWalker walker;

	orange::translate::TranslateVisitor visitor(walker, module);
	visitor.SetCurrentBlock(body);
	visitor.SetCurrentContext(tr.GenerateTypeTable()->GetGlobalContext());
	visitor.VisitLongBlockExpr(&ast);

	return visitor.GetValue(node);
}

TEST(Translator, BasicMainTranslate) {
	auto node = CreateNode<ReturnStmt>(CreateNode<IntValue>(5));

	auto term = CompileValueForNode(node);

	ASSERT_TRUE(term != nullptr);
	ASSERT_TRUE(isa<ReturnInst>(term));

	auto retVal = dyn_cast<ReturnInst>(term)->getReturnValue();

	ASSERT_TRUE(retVal != nullptr);
	ASSERT_TRUE(isa<ConstantInt>(retVal));

	EXPECT_EQ(5, llvm::dyn_cast<ConstantInt>(retVal)->getValue());

	delete node;
}

TEST(Translator, ArithBinOpExpr) {
	std::map<Node*, int> intBinOps = {
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::ADD,         CreateNode<IntValue>(23)), 15 +  23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::SUBTRACT,    CreateNode<IntValue>(23)), 15 -  23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::MULTIPLY,    CreateNode<IntValue>(23)), 15 *  23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::DIVIDE,      CreateNode<IntValue>(23)), 15 /  23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::REMAINDER,   CreateNode<IntValue>(23)), 15 %  23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::SHIFT_RIGHT, CreateNode<IntValue>(23)), 15 >> 23},
		{CreateNode<BinOpExpr>(CreateNode<IntValue>(15), BinOp::SHIFT_LEFT,  CreateNode<IntValue>(23)), 15 << 23},
	};

	auto a = 15.95;
	auto b = 95.12;
	std::map<Node*, double> fpBinOps = {
		{CreateNode<BinOpExpr>(CreateNode<DoubleValue>(a), BinOp::ADD,         CreateNode<DoubleValue>(b)), a +  b},
		{CreateNode<BinOpExpr>(CreateNode<DoubleValue>(a), BinOp::SUBTRACT,    CreateNode<DoubleValue>(b)), a -  b},
		{CreateNode<BinOpExpr>(CreateNode<DoubleValue>(a), BinOp::MULTIPLY,    CreateNode<DoubleValue>(b)), a *  b},
		{CreateNode<BinOpExpr>(CreateNode<DoubleValue>(a), BinOp::DIVIDE,      CreateNode<DoubleValue>(b)), a /  b},
	};

	for (auto kvp : intBinOps) {
		auto val = CompileValueForNode(kvp.first);
		ASSERT_TRUE(val != nullptr);
		ASSERT_TRUE(isa<ConstantInt>(val));

		EXPECT_EQ(kvp.second, dyn_cast<ConstantInt>(val)->getValue());

		delete kvp.first;
	}

	for (auto kvp : fpBinOps) {
		auto val = CompileValueForNode(kvp.first);
		ASSERT_TRUE(val != nullptr);
		ASSERT_TRUE(isa<ConstantFP>(val));

		EXPECT_FLOAT_EQ(kvp.second, dyn_cast<ConstantFP>(val)->getValueAPF().convertToDouble());

		delete kvp.first;
	}
}
