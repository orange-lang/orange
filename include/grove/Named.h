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
	
	/// Gets the mangled name of this node.
	virtual std::string getMangledName() const;

	/// Determines whether or not a name matches this node.
	/// @param name The name to compare against.
	virtual bool matchesName(std::string name) const;
};
