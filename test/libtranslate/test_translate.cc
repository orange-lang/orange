//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <gtest/gtest.h>
#include <sstream>

#include <libtranslate/translate.h>
#include <libanalysis/analyze.h>
#include <libast/ast.h>

using namespace orange::ast;
using namespace orange::translate;
using namespace orange::analysis;

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>

using namespace llvm;

std::shared_ptr<llvm::Module> CompileAST(LongBlockExpr* ast) {
	std::vector<LongBlockExpr *> astList = { ast };
	TypeResolution tr(astList);

	auto tt = tr.GenerateTypeTable();
	Translator t(tt);

	return t.TranslateMain(ast, "main.or");
}

TEST(Translator, BasicMainTranslate) {
	LongBlockExpr* ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<ReturnStmt>(CreateNode<IntValue>(5))
	}));

	auto mod = CompileAST(ast);
	auto term = mod->getFunction("main")->getEntryBlock().getTerminator();

	ASSERT_TRUE(isa<ReturnInst>(term));

	auto retVal = dyn_cast<ReturnInst>(term)->getReturnValue();

	ASSERT_TRUE(retVal != nullptr);
	ASSERT_TRUE(isa<ConstantInt>(retVal));

	EXPECT_EQ(5, llvm::dyn_cast<ConstantInt>(retVal)->getValue());

	delete ast;
}
