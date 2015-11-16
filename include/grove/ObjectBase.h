/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

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
		auto casted = dynamic_cast<T>(this);

		if (casted == nullptr)
		{
			throw std::runtime_error("object could not be casted to type");
		}

		return casted;
	}

	virtual ~ObjectBase()
	{
		// Do nothing.
	}
};
