/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include "ObjectBase.h"

#include <vector>

class Type;

/**
 * Named is an interface to define any node with a name that should be 
 * searchable.
 *
 * Nodes with duplicate names (like functions) may exist, but have different 
 * underlying types. For nodes such as these, a type hint must be used to 
 * determine the node to match. Type hints can use var types to be a wildcard.
 */
class Named : public ObjectBase {
protected:
	std::string m_name;
public:
	/// Gets the name of this node.
	std::string getName() const;

	/// Determines whether or not a name matches this node.
	/// @param name The name to compare against.
	virtual bool matches(std::string name) const;

	/// Determines whether or not a name matches this node.
	/// @param name The name to compare against.
	/// @param type A type to narrow down the list of candidates if
	/// multiple candidates exist. type can be a basic type, or a FunctionType,
	/// or any other compound type.
	virtual bool matches(std::string name, Type* type) const;
};
