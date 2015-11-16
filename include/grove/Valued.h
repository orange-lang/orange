/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "ObjectBase.h"

namespace llvm { class Value; }

/**
 * Valued is an interface to define any node with a value.
 * Those nodes are not necessarily expressions.
 */
class Valued : public ObjectBase {
protected:
	llvm::Value* m_value = nullptr;
public:
	/// If this expression points to a memory location (like a variable),
	/// gets the pointer where that expression is stored.
	virtual llvm::Value* getPointer() const;

	/// Determines whether or not getPointer will return a non-null value.
	/// True in the case of pointers.
	virtual bool hasPointer() const;

	virtual llvm::Value* getValue() const;
	virtual void setValue(llvm::Value* newValue);
};
