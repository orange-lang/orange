/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

class Type;

#include "exceptions/fatal_error.h"

class ObjectBase
{
public:
	/// Returns whether or not this node is a type.
	template <typename T> bool is()
	{
		return dynamic_cast<T>(this) != nullptr;
	}

	/// Casts this node to a certain type.
	template <typename T> T as()
	{
		// Hack out a way to check if this == nullptr
		void* ptr = this;
		if (ptr == nullptr)
		{
			throw fatal_error("trying casting a null object to a type");
		}
		
		auto casted = dynamic_cast<T>(this);

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
