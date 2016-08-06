//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <vector>
#include <map>

#include <libast/ast.h>
#include <libast/type.h>
#include <libast/search.h>

#include "error.h"

namespace orange { namespace analysis {
	class TypeTable;

	class TypeResolution {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
		AnalysisMessageLog mLog;
	public:
		/// Creates a type table with a global context for each AST, and then fills in the types for each.
		TypeTable* GenerateTypeTable();

		const AnalysisMessageLog GetLog() const;

		TypeResolution(orange::ast::LongBlockExpr* ast);
		TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs);
	};

	/// Validates that an AST is well-formed and isn't missing any required components
	bool ValidateAST(orange::ast::LongBlockExpr* AST, orange::ast::Walker* walker);
}}