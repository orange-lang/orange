/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

namespace Orange { class Type; }

#include "exceptions/fatal_error.h"

class ObjectBase
{
public:
	/// Returns whether or not this node is a type.
	template <typename T> bool is() const
	{
		return dynamic_cast<T>((ObjectBase *)this) != nullptr;
	}

	/// Casts this node to a certain type.
	template <typename T> T as() const
	{
		// Hack out a way to check if this == nullptr
		void* ptr = (ObjectBase *)this;
		if (ptr == nullptr)
		{
			throw fatal_error("trying casting a null object to a type");
		}
		
		auto casted = dynamic_cast<T>((ObjectBase *)this);

		if (casted == nullptr)
		{
			throw fatal_error("object could not be casted to wanted type");
		}

		return casted;
	}
	
	virtual ~ObjectBase()
	{
		// Do nothing.
	}
};
