/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Comparison.h"
#include "ObjectBase.h"

namespace Orange { class Type; }

namespace llvm { class Type; }

/**
 * Typed is an interface for elements that do have a type.
 */
class Typed : virtual public ObjectBase {
protected:
	const Orange::Type* m_type = nullptr;
public:
	/// Returns the current type.
	const Orange::Type* getType() const;

	/// Returns the LLVM type. Equivalent to getType()->getLLVMType().
	llvm::Type* getLLVMType() const;
	
	/// Determines whether or not this type matches another type.
	virtual bool matchesType(const Orange::Type* ty) const;

	/// Compare the types of a source against a target.
	static Comparison compare(const Typed* source, const Typed* target);

	/// Overrides the type.
	virtual void setType(const Orange::Type* type);
};
