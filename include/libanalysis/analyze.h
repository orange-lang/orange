//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <vector>

#include <libast/ast.h>
#include <libast/type.h>

namespace orange { namespace analysis {
	class TypeTable {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
	public:
		orange::ast::Type* GetNodeType(orange::ast::Node* node);
	};

	class TypeResolution {
	private:
		std::vector<orange::ast::LongBlockExpr*> mASTs;
	public:
		TypeTable* GenerateTypeTable();

		TypeResolution(std::vector<orange::ast::LongBlockExpr*> ASTs);
	};
}}