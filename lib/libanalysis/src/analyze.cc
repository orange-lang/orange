//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libast/typecheck.h>
#include <libast/walker.h>
#include <libanalysis/analyze.h>
#include <libanalysis/typetable.h>
#include <libanalysis/context.h>

#include "resolve.h"

using namespace orange::analysis;

TypeTable* TypeResolution::GenerateTypeTable() {
	// TODO: there's a use-after-free bug here.
	DefaultASTSearcher searcher(mASTs);
	DepthFirstWalker walker(TraversalOrder::POSTORDER);
	auto tt = new TypeTable(searcher, walker);
	
	// Create a global context for each AST.
	for (auto ast : mASTs) {
		auto ctx = new NodeTypeContext(ast, true);
		tt->AddGlobalContext(ctx);
	}
	
	// Resolve each context.
	for (auto ctx : tt->GetGlobalContexts()) {
		ResolveVisitor resolver(tt, ctx, mLog);
		
		walker.WalkLongBlockExpr(&resolver, asA<LongBlockExpr>(ctx->GetNode()));
	}
	
	return tt;
}

const AnalysisMessageLog TypeResolution::GetLog() const { return mLog; }

TypeResolution::TypeResolution(orange::ast::LongBlockExpr* ast) {
	mASTs.push_back(ast);
}

TypeResolution::TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs) : mASTs(ASTs) { }
