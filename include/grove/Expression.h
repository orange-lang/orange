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
#include "Valued.h"

namespace llvm { class Value; }

/**
 * Expression is the base class for elements that have values and types.
 */
class Expression : public ASTNode, public Valued, public Typed {
public:
	/// Casts the value of this expression to another type.
	/// Returns the result of that cast. The original value is untouched.
	llvm::Value* castTo(const Orange::Type* ty) const;
	
	/// Casts the value of this expression to the type of another expression.
	/// Returns the result of that cast. The original value is untouched.
	llvm::Value* castTo(Expression* expr) const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	/// Returns whether or not this expression represents a constant value.
	virtual bool isConstant() const;
};

