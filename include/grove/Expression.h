/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ASTNode.h"
#include "Typed.h"

namespace llvm { class Value; }

/**
 * Expression is the base class for elements that have values and types.
 */
class Expression : public ASTNode, public Typed {
protected:
	llvm::Value* m_value = nullptr;
public:
	/// Gets the value for this expression.
	llvm::Value* getValue() const;
	
	/// Sets the value for this expression.
	void setValue(llvm::Value* value);
};

