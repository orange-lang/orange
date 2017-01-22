/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

namespace orange { namespace ast { 
	struct Type { };

	struct IntType : Type { };
	struct FloatType : Type { };
	struct DoubleType : Type { };
	struct BoolType : Type { };
	struct CharType : Type { };
	struct ArrayType : Type { };
	struct PointerType : Type { };
	struct NamedType : Type { };
}}
