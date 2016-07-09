//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <gtest/gtest.h>
#include <map>
#include <functional>

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

struct CompilationContext {
	std::shared_ptr<Module> module;
	llvm::Function* function;
	llvm::BasicBlock* functionBody;
	orange::ast::NonTraversalWalker& walker;
	orange::translate::TranslateVisitor& visitor;

	CompilationContext(std::shared_ptr<Module> mod, llvm::Function* function, llvm::BasicBlock* bb,
		orange::ast::NonTraversalWalker& walker, orange::translate::TranslateVisitor& visitor) :
		module(mod), function(function), functionBody(bb), walker(walker), visitor(visitor) { }
};

typedef std::function<void(CompilationContext)> ValueCallback;
llvm::Value* CompileValueForNode(Node* node, Optional<ValueCallback> cb = Optional<ValueCallback>()) {
	LongBlockExpr ast (std::vector<Node*>({ node }));
	std::vector<LongBlockExpr *> astList = { &ast };
	TypeResolution tr(astList);

	auto module = std::make_shared<Module>("main.or", getGlobalContext());

	// Build the main function first
	auto mainTy = llvm::FunctionType::get(IntegerType::get(getGlobalContext(), 32), false);
	auto mainFunction = Function::Create(mainTy, GlobalValue::LinkageTypes::ExternalLinkage, "main", module.get());

	auto body = llvm::BasicBlock::Create(getGlobalContext(), "body", mainFunction);

	orange::ast::NonTraversalWalker walker;

	auto searcher = orange::ast::ASTSearcher(astList);
	orange::translate::TranslateVisitor visitor(walker, module, searcher);
	visitor.SetCurrentBlock(body);
	visitor.SetCurrentContext(tr.GenerateTypeTable()->GetGlobalContext());
	visitor.VisitLongBlockExpr(&ast);

	if (cb.hasValue()) {
		cb.getValue()(CompilationContext(module, mainFunction, body, walker, visitor));
	}

	// Always override loading values
	return visitor.GetValue(node, true);
}

TEST(Translator, TranslatesBools) {
	auto node = CreateNode<BoolValue>(true);

	CompileValueForNode(node, Optional<ValueCallback>([node] (CompilationContext ctx) {
		auto val = ctx.visitor.GetValue(node, true);

		ASSERT_TRUE(val != nullptr);
		ASSERT_TRUE(isa<ConstantInt>(val));

		EXPECT_EQ(true, llvm::dyn_cast<ConstantInt>(val)->getValue());
	}));

	delete node;
}

TEST(Translator, BasicMainTranslate) {
	auto node = CreateNode<ReturnStmt>(CreateNode<IntValue>(5));

	CompileValueForNode(node, Optional<ValueCallback>([node] (CompilationContext ctx) {
		auto term = ctx.visitor.GetValue(node, true);

		ASSERT_TRUE(term != nullptr);
		ASSERT_TRUE(isa<ReturnInst>(term));

		auto retVal = dyn_cast<ReturnInst>(term)->getReturnValue();

		ASSERT_TRUE(retVal != nullptr);
		ASSERT_TRUE(isa<ConstantInt>(retVal));

		EXPECT_EQ(5, llvm::dyn_cast<ConstantInt>(retVal)->getValue());
	}));

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
		auto node = kvp.first;

		CompileValueForNode(node, Optional<ValueCallback>([node, &kvp] (CompilationContext ctx) {
			auto val = ctx.visitor.GetValue(node, true);

			ASSERT_TRUE(val != nullptr);
			ASSERT_TRUE(isa<ConstantInt>(val));

			EXPECT_EQ(kvp.second, dyn_cast<ConstantInt>(val)->getValue());
		}));

		delete node;
	}

	for (auto kvp : fpBinOps) {
		auto node = kvp.first;

		CompileValueForNode(node, Optional<ValueCallback>([node, &kvp] (CompilationContext ctx) {
			auto val = ctx.visitor.GetValue(node, true);

			ASSERT_TRUE(val != nullptr);
			ASSERT_TRUE(isa<ConstantFP>(val));

			EXPECT_FLOAT_EQ(kvp.second, dyn_cast<ConstantFP>(val)->getValueAPF().convertToDouble());
		}));

		delete node;
	}
}

void ExpectInsts(Node* node, std::vector<unsigned> expect) {
	CompileValueForNode(node, Optional<ValueCallback>([node, expect] (CompilationContext ctx) {
		auto it = ctx.functionBody->begin();

		ctx.module->dump();

		for (auto inst : expect) {
			ASSERT_TRUE(it != ctx.functionBody->end());
			EXPECT_STREQ(Instruction::getOpcodeName(inst), it->getOpcodeName());

			it++;
		}

		EXPECT_TRUE(it == ctx.functionBody->end());
	}));
}

TEST(Translator, VarDeclNoValue) {
	auto varDecl = CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<orange::ast::Type*>({ new IntType }), nullptr
	);

	std::vector<unsigned> expectedInstructs({
		Instruction::MemoryOps::Alloca
	});


	ExpectInsts(varDecl, expectedInstructs);
	delete varDecl;
}

TEST(Translator, SingleVarDecl) {
	auto varDecl = CreateNode<VarDeclExpr>(
		std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
		std::vector<orange::ast::Type*>({}),
		CreateNode<IntValue>(951)
	);

	std::vector<unsigned> expectedInstructs({
		Instruction::MemoryOps::Alloca,
	    Instruction::MemoryOps::Store
	});


	ExpectInsts(varDecl, expectedInstructs);
	delete varDecl;
}

TEST(Translator, VarDeclReference) {
	auto ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<orange::ast::Type*>({}),
			CreateNode<IntValue>(951)
		),

	    CreateNode<ReferenceIDExpr>("a")
	}));

	std::vector<unsigned> expectedInstructs({
		Instruction::MemoryOps::Alloca,
	    Instruction::MemoryOps::Store,
	});

	ExpectInsts(ast, expectedInstructs);
	delete ast;
}

TEST(Translator, AssignBinOps) {
	auto ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<VarDeclExpr>(
			std::vector<Identifier*>({ CreateNode<NamedIDExpr>("a") }),
			std::vector<orange::ast::Type*>(), CreateNode<IntValue>(5)
		),

		CreateNode<BinOpExpr>(
			CreateNode<ReferenceIDExpr>("a"),
			BinOp::PLUS_ASSIGN,
			CreateNode<IntValue>(5)
		),

	    CreateNode<BinOpExpr>(
		 	CreateNode<ReferenceIDExpr>("a"),
			BinOp::ASSIGN,
			CreateNode<IntValue>(10)
	    )
	}));

	std::vector<unsigned> expectedInstructs({
		Instruction::MemoryOps::Alloca,
		Instruction::MemoryOps::Store,
	    Instruction::MemoryOps::Load,
	    Instruction::BinaryOps::Add,
	    Instruction::MemoryOps::Store,
		Instruction::MemoryOps::Store
	});

	ExpectInsts(ast, expectedInstructs);
	delete ast;
}