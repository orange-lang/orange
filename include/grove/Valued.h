/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

namespace llvm { class Value; }

/**
 * Valued is an interface to define any node with a value.
 * Those nodes are not necessarily expressions.
 */
class Valued {
protected:
	llvm::Value* m_value = nullptr;
public:
	llvm::Value* getValue() const;
	void setValue(llvm::Value* newValue);
};
