//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <libast/type.h>

namespace orange { namespace analysis {
	/// Determines whether or not two types are compatible for an operation via implicit casting
	bool AreTypesCompatible(orange::ast::Type* a, orange::ast::Type* b);

	/// Gets the type that is of higher precedence in an operation between multiple types
	/// If the types are not compatible, returns nullptr.
	orange::ast::Type* GetImplicitType(orange::ast::Type* a, orange::ast::Type* b);
}}