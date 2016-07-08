//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <libast/ast.h>
#include <libanalysis/analyze.h>

#include <llvm/IR/Module.h>
#include <memory>
#include <string>

namespace orange { namespace translate {
	class Translator {
	private:
		analysis::TypeTable* mTypeTable = nullptr;
	public:
		/// Gets the type table given to this AST.
		analysis::TypeTable* GetTypeTable() const;

		/// Translates an AST into a code module.
		/// Code modules ignore most statements in the global block.
		std::shared_ptr<llvm::Module> Translate(ast::LongBlockExpr* ast, std::string name);

		// Translates an AST into a main module, complete with a main function.
		std::shared_ptr<llvm::Module> TranslateMain(ast::LongBlockExpr* ast, std::string name);

		/// Constructs a new translator. A translator must be given a type table 
		/// that has type info for each AST that will be translated.
		Translator(analysis::TypeTable* typeInfo);
	};
}}
