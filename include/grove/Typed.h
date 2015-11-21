/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Comparison.h"
#include "ObjectBase.h"

class Type;

namespace llvm { class Type; }

/**
 * Typed is an interface for elements that do have a type.
 */
class Typed : public ObjectBase {
protected:
	Type* m_type = nullptr;
public:
	/// Returns the current type.
	Type* getType() const;

	/// Returns the LLVM type. Equivalent to getType()->getLLVMType().
	llvm::Type* getLLVMType() const;
	
	/// Determines whether or not this type matches another type.
	virtual bool matchesType(Type* ty) const;

	/// Compare the types of a source against a target.
	static Comparison compare(Typed* source, Typed* target);

	/// Overrides the type.
	void setType(Type* type);
};
