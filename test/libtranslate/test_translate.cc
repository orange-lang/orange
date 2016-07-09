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

TEST(Translator, BasicMainTranslate) {
	LongBlockExpr* ast = CreateNode<LongBlockExpr>(std::vector<Node*>({
		CreateNode<ReturnStmt>(CreateNode<IntValue>(5))
	}));

	std::vector<LongBlockExpr *> astList = { ast };
	TypeResolution tr(astList);

	auto tt = tr.GenerateTypeTable();
	Translator t(tt);

	auto mod = t.TranslateMain(ast, "main.or");
	mod->dump();

	delete ast;
}
